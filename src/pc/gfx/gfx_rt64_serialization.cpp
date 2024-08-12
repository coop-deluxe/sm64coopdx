#ifdef RAPI_RT64

#include "gfx_rt64.h"
#include "gfx_rt64_context.h"
#include "gfx_rt64_geo_map.h"
#include "gfx_rt64_serialization.h"

#include <fstream>
#include <iomanip>

#include "json/json.hpp"

using json = nlohmann::json;

extern "C" {
#	include "../fs/fs.h"
}

#define LEVEL_LIGHTS_FILENAME			FS_BASEDIR "/rt64/level_lights.json"
#define GEO_LAYOUT_MODS_FILENAME		FS_BASEDIR "/rt64/geo_layout_mods.json"
#define TEXTURE_MODS_FILENAME			FS_BASEDIR "/rt64/texture_mods.json"

RT64_VECTOR3 gfx_rt64_load_vector3(const json &jobject, const std::string &key, RT64_VECTOR3 def = { 0.0f, 0.0f, 0.0f }) {
	auto it = jobject.find(key);
	if (it != jobject.end()) {
		const json &jvector = (*it);
		if (jvector.size() == 3) {
			return { jvector[0], jvector[1], jvector[2] };
		}
	}

	return def;
}

json gfx_rt64_save_vector3(RT64_VECTOR3 v) {
	return { v.x, v.y, v.z };
}

static inline size_t string_hash(const uint8_t *str) {
    size_t h = 0;
    for (const uint8_t *p = str; *p; p++)
        h = 31 * h + *p;
    return h;
}

uint64_t gfx_rt64_get_texture_name_hash(const std::string &name) {
	uint64_t hash = string_hash((const uint8_t *)(name.c_str()));
	RT64.texNameMap[hash] = name;
	RT64.nameTexMap[name] = hash;
	return hash;
}

uint64_t gfx_rt64_load_normal_map_mod(const json &jnormal) {
	return gfx_rt64_get_texture_name_hash(jnormal["name"]);
}

uint64_t gfx_rt64_load_specular_map_mod(const json &jspecular) {
	return gfx_rt64_get_texture_name_hash(jspecular["name"]);
}

json gfx_rt64_save_normal_map_mod(const std::string &normalTexName) {
	json jnormal;
	jnormal["name"] = normalTexName;
	return jnormal;
}

json gfx_rt64_save_specular_map_mod(const std::string &specularTexName) {
	json jspecular;
	jspecular["name"] = specularTexName;
	return jspecular;
}

void gfx_rt64_load_light(const json &jlight, RT64_LIGHT *light) {
	// General parameters
	light->position = gfx_rt64_load_vector3(jlight, "position");
	light->attenuationRadius = jlight["attenuationRadius"];
	light->pointRadius = jlight["pointRadius"];
	light->diffuseColor = gfx_rt64_load_vector3(jlight, "diffuseColor");
	light->shadowOffset = jlight["shadowOffset"];
	light->attenuationExponent = jlight["attenuationExponent"];
	light->flickerIntensity = jlight["flickerIntensity"];
	light->groupBits = jlight["groupBits"];

	// Backwards compatibility
	if (jlight.find("specularIntensity") != jlight.end()) {
		float specularIntensity = jlight["specularIntensity"];
		light->specularColor.x = specularIntensity * light->diffuseColor.x;
		light->specularColor.y = specularIntensity * light->diffuseColor.y;
		light->specularColor.z = specularIntensity * light->diffuseColor.z;
	}
	
	// New parameters
	light->specularColor = gfx_rt64_load_vector3(jlight, "specularColor", light->specularColor);
}

json gfx_rt64_save_light(RT64_LIGHT *light) {
	json jlight;
	jlight["position"] = gfx_rt64_save_vector3(light->position);
	jlight["attenuationRadius"] = light->attenuationRadius;
	jlight["pointRadius"] = light->pointRadius;
	jlight["diffuseColor"] = gfx_rt64_save_vector3(light->diffuseColor);
	jlight["specularColor"] = gfx_rt64_save_vector3(light->specularColor);
	jlight["shadowOffset"] = light->shadowOffset;
	jlight["attenuationExponent"] = light->attenuationExponent;
	jlight["flickerIntensity"] = light->flickerIntensity;
	jlight["groupBits"] = light->groupBits;
	return jlight;
}

void gfx_rt64_load_scene_description(const json &jscene, RT64_SCENE_DESC *sceneDesc) {
	sceneDesc->ambientBaseColor = gfx_rt64_load_vector3(jscene, "ambientBaseColor");
	sceneDesc->ambientNoGIColor = gfx_rt64_load_vector3(jscene, "ambientNoGIColor");
	sceneDesc->eyeLightDiffuseColor = gfx_rt64_load_vector3(jscene, "eyeLightDiffuseColor");
	sceneDesc->eyeLightSpecularColor = gfx_rt64_load_vector3(jscene, "eyeLightSpecularColor");
	sceneDesc->skyDiffuseMultiplier = gfx_rt64_load_vector3(jscene, "skyDiffuseMultiplier", { 1.0f, 1.0f, 1.0f });
	sceneDesc->skyHSLModifier = gfx_rt64_load_vector3(jscene, "skyHSLModifier");
	sceneDesc->skyYawOffset = jscene.value("skyYawOffset", 0.0f);
	sceneDesc->giDiffuseStrength = jscene.value("giDiffuseStrength", 0.7f);
	sceneDesc->giSkyStrength = jscene.value("giSkyStrength", 0.35f);
}

json gfx_rt64_save_scene_description(RT64_SCENE_DESC *sceneDesc) {
	json jscene;
	jscene["ambientBaseColor"] = gfx_rt64_save_vector3(sceneDesc->ambientBaseColor);
	jscene["ambientNoGIColor"] = gfx_rt64_save_vector3(sceneDesc->ambientNoGIColor);
	jscene["eyeLightDiffuseColor"] = gfx_rt64_save_vector3(sceneDesc->eyeLightDiffuseColor);
	jscene["eyeLightSpecularColor"] = gfx_rt64_save_vector3(sceneDesc->eyeLightSpecularColor);
	jscene["skyDiffuseMultiplier"] = gfx_rt64_save_vector3(sceneDesc->skyDiffuseMultiplier);
	jscene["skyHSLModifier"] = gfx_rt64_save_vector3(sceneDesc->skyHSLModifier);
	jscene["skyYawOffset"] = sceneDesc->skyYawOffset;
	jscene["giDiffuseStrength"] = sceneDesc->giDiffuseStrength;
	jscene["giSkyStrength"] = sceneDesc->giSkyStrength;
	return jscene;
}

void gfx_rt64_default_level_lights() {
	for (int l = 0; l < MAX_LEVELS; l++) {
        for (int a = 0; a < MAX_AREAS; a++) {
			auto &areaLighting = RT64.levelAreaLighting[l][a];
			memset(areaLighting.lights, 0, sizeof(areaLighting.lights));
			areaLighting.lightCount = 0;

			// Configure the default area lighting scene description.
			auto &sceneDesc = areaLighting.sceneDesc;
			sceneDesc.ambientBaseColor = { 0.20f, 0.20f, 0.25f };
			sceneDesc.ambientNoGIColor = { 0.10f, 0.15f, 0.20f };
			sceneDesc.eyeLightDiffuseColor = { 0.1f, 0.1f, 0.1f };
			sceneDesc.eyeLightSpecularColor = { 0.1f, 0.1f, 0.1f };
			sceneDesc.skyDiffuseMultiplier = { 1.0f, 1.0f, 1.0f };
			sceneDesc.skyHSLModifier = { 0.0f, 0.0f, 0.0f };
			sceneDesc.skyYawOffset = 0.0f;
			sceneDesc.giDiffuseStrength = 0.7f;
			sceneDesc.giSkyStrength = 0.35f;

			// Configure a default directional sun.
			RT64_LIGHT &light = areaLighting.lights[0];
            light.position.x = 100000.0f;
            light.position.y = 200000.0f;
            light.position.z = 100000.0f;
            light.diffuseColor.x = 0.8f;
            light.diffuseColor.y = 0.75f;
            light.diffuseColor.z = 0.65f;
            light.attenuationRadius = 1e11;
			light.pointRadius = 5000.0f;
            light.specularColor = { 0.8f, 0.75f, 0.65f };
            light.shadowOffset = 0.0f;
            light.attenuationExponent = 0.0f;
			light.groupBits = RT64_LIGHT_GROUP_DEFAULT;
            areaLighting.lightCount = 1;
        }
    }
}

void gfx_rt64_load_level_lights() {
	std::ifstream i(LEVEL_LIGHTS_FILENAME);
	if (i.is_open()) {
		json j;
		i >> j;

		for (const json &jlevel : j["levels"]) {
			unsigned int l = jlevel["id"];
			assert(l < MAX_LEVELS);
			for (const json &jarea : jlevel["areas"]) {
				unsigned int a = jarea["id"];
				assert(a < MAX_AREAS);
				RT64.levelAreaLighting[l][a].lightCount = 0;
				if (jarea.find("lights") != jarea.end()) {
					for (const json &jlight : jarea["lights"]) {
						assert(RT64.levelAreaLighting[l][a].lightCount < MAX_LEVEL_LIGHTS);
						unsigned int i = RT64.levelAreaLighting[l][a].lightCount++;
						RT64_LIGHT *light = &RT64.levelAreaLighting[l][a].lights[i];
						gfx_rt64_load_light(jlight, light);
					}
				}

				if (jarea.find("scene") != jarea.end()) {
					RT64_SCENE_DESC *sceneDesc = &RT64.levelAreaLighting[l][a].sceneDesc;
					gfx_rt64_load_scene_description(jarea["scene"], sceneDesc);
				}
			}
		}
	}
	else {
		fprintf(stderr, "Unable to load " LEVEL_LIGHTS_FILENAME ". Using default lighting.\n");
	}
}

void gfx_rt64_save_level_lights() {
	std::ofstream o(LEVEL_LIGHTS_FILENAME);
	if (o.is_open()) {
		json jroot;
		for (int l = 0; l < MAX_LEVELS; l++) {
			json jlevel;
			jlevel["id"] = l;

			for (int a = 0; a < MAX_AREAS; a++) {
				json jarea;
				jarea["id"] = a;
				for (int i = 0; i < RT64.levelAreaLighting[l][a].lightCount; i++) {
					json jlight;
					RT64_LIGHT *light = &RT64.levelAreaLighting[l][a].lights[i];
					jlight = gfx_rt64_save_light(light);
					jarea["lights"].push_back(jlight);
				}

				RT64_SCENE_DESC *sceneDesc = &RT64.levelAreaLighting[l][a].sceneDesc;
				jarea["scene"] = gfx_rt64_save_scene_description(sceneDesc);

				jlevel["areas"].push_back(jarea);
			}

			jroot["levels"].push_back(jlevel);
		}

		o << std::setw(4) << jroot << std::endl;

		if (o.bad()) {
			fprintf(stderr, "Error when saving " LEVEL_LIGHTS_FILENAME ".\n");
		}
		else {
			fprintf(stderr, "Saved " LEVEL_LIGHTS_FILENAME ".\n");
		}
	}
	else {
		fprintf(stderr, "Unable to save " LEVEL_LIGHTS_FILENAME ".\n");
	}
}

void gfx_rt64_load_material_mod_uint(const json &jmatmod, RT64_MATERIAL *materialMod, const char *name, int flag, unsigned int *dstValue, int *dstAttributes) {
	if (jmatmod.find(name) != jmatmod.end()) {
		*dstValue = jmatmod[name];
		*dstAttributes = (*dstAttributes) | flag;
	}
}

void gfx_rt64_load_material_mod_float(const json &jmatmod, RT64_MATERIAL *materialMod, const char *name, int flag, float *dstValue, int *dstAttributes) {
	if (jmatmod.find(name) != jmatmod.end()) {
		*dstValue = jmatmod[name];
		*dstAttributes = (*dstAttributes) | flag;
	}
}

void gfx_rt64_load_material_mod_vector3(const json &jmatmod, RT64_MATERIAL *materialMod, const char *name, int flag, RT64_VECTOR3 *dstValue, int *dstAttributes) {
	if (jmatmod.find(name) != jmatmod.end()) {
		dstValue->x = jmatmod[name][0];
		dstValue->y = jmatmod[name][1];
		dstValue->z = jmatmod[name][2];
		*dstAttributes = (*dstAttributes) | flag;
	}
}

void gfx_rt64_load_material_mod_vector4(const json &jmatmod, RT64_MATERIAL *materialMod, const char *name, int flag, RT64_VECTOR4 *dstValue, int *dstAttributes) {
	if (jmatmod.find(name) != jmatmod.end()) {
		dstValue->x = jmatmod[name][0];
		dstValue->y = jmatmod[name][1];
		dstValue->z = jmatmod[name][2];
		dstValue->w = jmatmod[name][3];
		*dstAttributes = (*dstAttributes) | flag;
	}
}

void gfx_rt64_load_material_mod(const json &jmatmod, RT64_MATERIAL *materialMod) {
	// Backwards compatibility
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "normalMapScale", RT64_ATTRIBUTE_UV_DETAIL_SCALE, &materialMod->uvDetailScale, &materialMod->enabledAttributes);
	if (jmatmod.find("specularIntensity") != jmatmod.end()) {
		float specularIntensity = jmatmod["specularIntensity"];
		materialMod->specularColor = { specularIntensity, specularIntensity, specularIntensity };
		materialMod->enabledAttributes |= RT64_ATTRIBUTE_SPECULAR_COLOR;
	}

	// Current version
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "ignoreNormalFactor", RT64_ATTRIBUTE_IGNORE_NORMAL_FACTOR, &materialMod->ignoreNormalFactor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "uvDetailScale", RT64_ATTRIBUTE_UV_DETAIL_SCALE, &materialMod->uvDetailScale, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "reflectionFactor", RT64_ATTRIBUTE_REFLECTION_FACTOR, &materialMod->reflectionFactor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "reflectionFresnelFactor", RT64_ATTRIBUTE_REFLECTION_FRESNEL_FACTOR, &materialMod->reflectionFresnelFactor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "reflectionShineFactor", RT64_ATTRIBUTE_REFLECTION_SHINE_FACTOR, &materialMod->reflectionShineFactor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "refractionFactor", RT64_ATTRIBUTE_REFRACTION_FACTOR, &materialMod->refractionFactor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_vector3(jmatmod, materialMod, "specularColor", RT64_ATTRIBUTE_SPECULAR_COLOR, &materialMod->specularColor, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "specularExponent", RT64_ATTRIBUTE_SPECULAR_EXPONENT, &materialMod->specularExponent, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "solidAlphaMultiplier", RT64_ATTRIBUTE_SOLID_ALPHA_MULTIPLIER, &materialMod->solidAlphaMultiplier, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "shadowAlphaMultiplier", RT64_ATTRIBUTE_SHADOW_ALPHA_MULTIPLIER, &materialMod->shadowAlphaMultiplier, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "depthBias", RT64_ATTRIBUTE_DEPTH_BIAS, &materialMod->depthBias, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_float(jmatmod, materialMod, "shadowRayBias", RT64_ATTRIBUTE_SHADOW_RAY_BIAS, &materialMod->shadowRayBias, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_vector3(jmatmod, materialMod, "selfLight", RT64_ATTRIBUTE_SELF_LIGHT, &materialMod->selfLight, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_uint(jmatmod, materialMod, "lightGroupMaskBits", RT64_ATTRIBUTE_LIGHT_GROUP_MASK_BITS, &materialMod->lightGroupMaskBits, &materialMod->enabledAttributes);
	gfx_rt64_load_material_mod_vector4(jmatmod, materialMod, "diffuseColorMix", RT64_ATTRIBUTE_DIFFUSE_COLOR_MIX, &materialMod->diffuseColorMix, &materialMod->enabledAttributes);
}

void gfx_rt64_save_material_mod_uint(json &jmatmod, RT64_MATERIAL *materialMod, int flag, const char *name, const unsigned int value) {
	if (materialMod->enabledAttributes & flag) {
		jmatmod[name] = value;
	}
}

void gfx_rt64_save_material_mod_float(json &jmatmod, RT64_MATERIAL *materialMod, int flag, const char *name, const float value) {
	if (materialMod->enabledAttributes & flag) {
		jmatmod[name] = value;
	}
}

void gfx_rt64_save_material_mod_vector3(json &jmatmod, RT64_MATERIAL *materialMod, int flag, const char *name, const RT64_VECTOR3 &value) {
	if (materialMod->enabledAttributes & flag) {
		jmatmod[name] = { value.x, value.y, value.z };
	}
}

void gfx_rt64_save_material_mod_vector4(json &jmatmod, RT64_MATERIAL *materialMod, int flag, const char *name, const RT64_VECTOR4 &value) {
	if (materialMod->enabledAttributes & flag) {
		jmatmod[name] = { value.x, value.y, value.z, value.w };
	}
}

json gfx_rt64_save_material_mod(RT64_MATERIAL *materialMod) {
	json jmatmod;
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_IGNORE_NORMAL_FACTOR, "ignoreNormalFactor", materialMod->ignoreNormalFactor);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_UV_DETAIL_SCALE, "uvDetailScale", materialMod->uvDetailScale);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_REFLECTION_FACTOR, "reflectionFactor", materialMod->reflectionFactor);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_REFLECTION_FRESNEL_FACTOR, "reflectionFresnelFactor", materialMod->reflectionFresnelFactor);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_REFLECTION_SHINE_FACTOR, "reflectionShineFactor", materialMod->reflectionShineFactor);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_REFRACTION_FACTOR, "refractionFactor", materialMod->refractionFactor);
	gfx_rt64_save_material_mod_vector3(jmatmod, materialMod, RT64_ATTRIBUTE_SPECULAR_COLOR, "specularColor", materialMod->specularColor);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_SPECULAR_EXPONENT, "specularExponent", materialMod->specularExponent);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_SOLID_ALPHA_MULTIPLIER, "solidAlphaMultiplier", materialMod->solidAlphaMultiplier);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_SHADOW_ALPHA_MULTIPLIER, "shadowAlphaMultiplier", materialMod->shadowAlphaMultiplier);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_DEPTH_BIAS, "depthBias", materialMod->depthBias);
	gfx_rt64_save_material_mod_float(jmatmod, materialMod, RT64_ATTRIBUTE_SHADOW_RAY_BIAS, "shadowRayBias", materialMod->shadowRayBias);
	gfx_rt64_save_material_mod_vector3(jmatmod, materialMod, RT64_ATTRIBUTE_SELF_LIGHT, "selfLight", materialMod->selfLight);
	gfx_rt64_save_material_mod_uint(jmatmod, materialMod, RT64_ATTRIBUTE_LIGHT_GROUP_MASK_BITS, "lightGroupMaskBits", materialMod->lightGroupMaskBits);
	gfx_rt64_save_material_mod_vector4(jmatmod, materialMod, RT64_ATTRIBUTE_DIFFUSE_COLOR_MIX, "diffuseColorMix", materialMod->diffuseColorMix);
	return jmatmod;
}

void gfx_rt64_load_geo_layout_mods() {
	RT64_MATERIAL *material;
	RT64_LIGHT *light;
	gfx_rt64_init_geo_layout_maps(RT64.geoLayoutNameMap, RT64.nameGeoLayoutMap);

	std::ifstream i(GEO_LAYOUT_MODS_FILENAME);
	if (i.is_open()) {
		json j;
		i >> j;

		for (const json &jgeo : j["geoLayouts"]) {
			std::string geoName = jgeo["name"];
			void *geoLayout = RT64.nameGeoLayoutMap[geoName];
			if (geoLayout != nullptr) {
				RecordedMod *recordedMod = new RecordedMod();
				if (jgeo.find("materialMod") != jgeo.end()) {
					material = new RT64_MATERIAL();
					material->enabledAttributes = RT64_ATTRIBUTE_NONE;
					gfx_rt64_load_material_mod(jgeo["materialMod"], material);
					recordedMod->materialMod = material;
				}
				else {
					recordedMod->materialMod = nullptr;
				}
				
				if (jgeo.find("lightMod") != jgeo.end()) {
					light = new RT64_LIGHT();
					gfx_rt64_load_light(jgeo["lightMod"], light);
					recordedMod->lightMod = light;
				}
				else {
					recordedMod->lightMod = nullptr;
				}

				// Parse normal map mod.
				if (jgeo.find("normalMapMod") != jgeo.end()) {
					recordedMod->normalMapHash = gfx_rt64_load_normal_map_mod(jgeo["normalMapMod"]);
				}
				else {
					recordedMod->normalMapHash = 0;
				}

				// Parse specular map mod.
				if (jgeo.find("specularMapMod") != jgeo.end()) {
					recordedMod->specularMapHash = gfx_rt64_load_specular_map_mod(jgeo["specularMapMod"]);
				}
				else {
					recordedMod->specularMapHash = 0;
				}

				// Parse interpolation mod.
				if (jgeo.find("interpolationEnabled") != jgeo.end()) {
					recordedMod->interpolationEnabled = jgeo["interpolationEnabled"];
				}
				else {
					recordedMod->interpolationEnabled = true;
				}

				RT64.geoLayoutMods[geoLayout] = recordedMod;
			}
			else {
				fprintf(stderr, "Error when loading " GEO_LAYOUT_MODS_FILENAME ". Geo layout %s is not recognized.\n", geoName.c_str());
			}
		}
	}
	else {
		fprintf(stderr, "Unable to load " GEO_LAYOUT_MODS_FILENAME ".\n");
	}
}

void gfx_rt64_save_geo_layout_mods() {
	std::ofstream o(GEO_LAYOUT_MODS_FILENAME);
	if (o.is_open()) {
		json jroot;
		for (const auto &pair : RT64.nameGeoLayoutMap) {
			const std::string geoName = pair.first;
			void *geoLayout = pair.second;
			auto it = RT64.geoLayoutMods.find(geoLayout);
			if (it != RT64.geoLayoutMods.end()) {
				json jgeo;
				RecordedMod *geoMod = it->second;
				jgeo["name"] = geoName;

				RT64_MATERIAL *materialMod = geoMod->materialMod;
				if (materialMod != nullptr) {
					jgeo["materialMod"] = gfx_rt64_save_material_mod(materialMod);
				}

				RT64_LIGHT *lightMod = geoMod->lightMod;
				if (lightMod != nullptr) {
					jgeo["lightMod"] = gfx_rt64_save_light(lightMod);
				}

				const std::string normName = RT64.texNameMap[geoMod->normalMapHash];
				if (!normName.empty()) {
					jgeo["normalMapMod"] = gfx_rt64_save_normal_map_mod(normName);
				}

				const std::string specName = RT64.texNameMap[geoMod->specularMapHash];
				if (!normName.empty()) {
					jgeo["specularMapMod"] = gfx_rt64_save_specular_map_mod(specName);
				}

				if (!geoMod->interpolationEnabled) {
					jgeo["interpolationEnabled"] = false;
				}
				
				jroot["geoLayouts"].push_back(jgeo);
			}
		}

		o << std::setw(4) << jroot << std::endl;
		
		if (o.bad()) {
			fprintf(stderr, "Error when saving " GEO_LAYOUT_MODS_FILENAME ".\n");
		}
		else {
			fprintf(stderr, "Saved " GEO_LAYOUT_MODS_FILENAME ".\n");
		}
	}
	else {
		fprintf(stderr, "Unable to save " GEO_LAYOUT_MODS_FILENAME ".\n");
	}
}

void gfx_rt64_load_texture_mods() {
	RT64_MATERIAL *material;
	RT64_LIGHT *light;
	std::ifstream i(TEXTURE_MODS_FILENAME);
	if (i.is_open()) {
		json j;
		i >> j;

		for (const json &jtex : j["textures"]) {
			uint64_t texHash = gfx_rt64_get_texture_name_hash(jtex["name"]);
			RT64.texMods[texHash] = new RecordedMod();

			// Parse material mod.
			if (jtex.find("materialMod") != jtex.end()) {
				material = new RT64_MATERIAL();
				material->enabledAttributes = RT64_ATTRIBUTE_NONE;
				gfx_rt64_load_material_mod(jtex["materialMod"], material);
				RT64.texMods[texHash]->materialMod = material;
			}
			else {
				RT64.texMods[texHash]->materialMod = nullptr;
			}
			
			// Parse light mod.
			if (jtex.find("lightMod") != jtex.end()) {
				light = new RT64_LIGHT();
				gfx_rt64_load_light(jtex["lightMod"], light);
				RT64.texMods[texHash]->lightMod = light;
			}
			else {
				RT64.texMods[texHash]->lightMod = nullptr;
			}

			// Parse normal map mod.
			if (jtex.find("normalMapMod") != jtex.end()) {
				RT64.texMods[texHash]->normalMapHash = gfx_rt64_load_normal_map_mod(jtex["normalMapMod"]);
			}
			else {
				RT64.texMods[texHash]->normalMapHash = 0;
			}

			// Parse specular map mod.
			if (jtex.find("specularMapMod") != jtex.end()) {
				RT64.texMods[texHash]->specularMapHash = gfx_rt64_load_specular_map_mod(jtex["specularMapMod"]);
			}
			else {
				RT64.texMods[texHash]->specularMapHash = 0;
			}

			// Parse texture name aliases.
			if (jtex.find("aliases") != jtex.end()) {
				for (const json &jalias : jtex["aliases"]) {
					uint64_t aliasHash = gfx_rt64_get_texture_name_hash(jalias);
					RT64.texHashAliasMap[aliasHash] = texHash;
					RT64.texHashAliasesMap[texHash].push_back(aliasHash);
				}
			}
		}
	}
	else {
		fprintf(stderr, "Unable to load " TEXTURE_MODS_FILENAME ".\n");
	}
}

void gfx_rt64_save_texture_mods() {
	std::ofstream o(TEXTURE_MODS_FILENAME);
	if (o.is_open()) {
		json jroot;
		for (const auto &pair : RT64.nameTexMap) {
			const std::string texName = pair.first;
			uint64_t texHash = pair.second;
			auto it = RT64.texMods.find(texHash);
			if (it != RT64.texMods.end()) {
				json jtex;
				RecordedMod *texMod = it->second;
				jtex["name"] = texName;

				RT64_MATERIAL *materialMod = texMod->materialMod;
				if (materialMod != nullptr) {
					jtex["materialMod"] = gfx_rt64_save_material_mod(materialMod);
				}

				RT64_LIGHT *lightMod = texMod->lightMod;
				if (lightMod != nullptr) {
					jtex["lightMod"] = gfx_rt64_save_light(lightMod);
				}

				const std::string normName = RT64.texNameMap[texMod->normalMapHash];
				if (!normName.empty()) {
					jtex["normalMapMod"] = gfx_rt64_save_normal_map_mod(normName);
				}

				const std::string specName = RT64.texNameMap[texMod->specularMapHash];
				if (!normName.empty()) {
					jtex["specularMapMod"] = gfx_rt64_save_specular_map_mod(specName);
				}

				const std::vector<uint64_t> aliasHashes = RT64.texHashAliasesMap[texHash];
				for (const auto &aliasHash : aliasHashes) {
					jtex["aliases"].push_back(RT64.texNameMap[aliasHash]);
				}

				jroot["textures"].push_back(jtex);
			}
		}

		o << std::setw(4) << jroot << std::endl;
		
		if (o.bad()) {
			fprintf(stderr, "Error when saving " TEXTURE_MODS_FILENAME ".\n");
		}
		else {
			fprintf(stderr, "Saved " TEXTURE_MODS_FILENAME ".\n");
		}
	}
	else {
		fprintf(stderr, "Unable to save " TEXTURE_MODS_FILENAME ".\n");
	}
}

#endif