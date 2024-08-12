#ifndef GFX_RT64_CONTEXT_H
#define GFX_RT64_CONTEXT_H

#include "rt64/rt64.h"

#include "gfx_rendering_api_config.h"

#include <atomic>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include <Windows.h>

#define MAX_GEO_LAYOUT_STACK_SIZE		32
#define CACHED_MESH_REQUIRED_FRAMES		5
#define CACHED_MESH_MAX_PER_FRAME		1
#define MAX_LIGHTS						512
#define MAX_LEVEL_LIGHTS				128
#define MAX_LEVELS						40
#define MAX_AREAS						3
#define MAX_MOUSE_BUTTONS				5
#define MAX_RENDER_FRAMES				4

struct ShaderProgram {
    uint32_t shaderId;
    uint8_t numInputs;
    bool usedTextures[2];
	std::unordered_map<uint16_t, RT64_SHADER *> shaderVariantMap;
};

struct RecordedTexture {
	bool linearFilter;
	uint32_t cms;
	uint32_t cmt;
	uint64_t hash;
};

struct RecordedMod {
    RT64_MATERIAL *materialMod = nullptr;
    RT64_LIGHT *lightMod = nullptr;
	uint64_t normalMapHash = 0;
	uint64_t specularMapHash = 0;
	bool interpolationEnabled = true;
};

struct AreaLighting {
	RT64_SCENE_DESC sceneDesc;
	RT64_LIGHT lights[MAX_LEVEL_LIGHTS];
	int lightCount = 0;
};

struct GameInstance {
	RT64_INSTANCE_DESC desc;
	bool interpolate = true;
	
	struct {
		uint32_t diffuse = 0;
		uint32_t normal = 0;
		uint32_t specular = 0;
	} textures;

	struct {
		ShaderProgram *program = nullptr;
		bool raytrace;
		int filter;
		int hAddr;
		int vAddr;
		bool normalMap;
		bool specularMap;
	} shader;

	RT64_LIGHT light;
};

struct GameMesh {
	float *vertexBuffer = nullptr;
	uint64_t vertexBufferHash = 0;
    uint32_t vertexCount = 0;
	uint32_t vertexStride = 0;
    uint32_t indexCount = 0;
	bool useTexture = false;
    bool raytrace = false;
};

struct GameDisplayList {
	std::vector<GameInstance> instances;
	std::vector<GameMesh> meshes;
	RT64_MATRIX4 transform;
	RT64_LIGHT light;
	int drawCount = 0;
	bool interpolateTransform = true;
};

struct GameFrame {
	RT64_MATRIX4 viewMatrix;
	RT64_MATRIX4 invViewMatrix;
	float fovRadians;
	float nearDist;
	float farDist;
	bool interpolateView = true;
	std::unordered_map<uint32_t, GameDisplayList> displayLists;
	RT64_SCENE_DESC sceneDesc;
	const RT64_LIGHT *areaLights = nullptr;
    unsigned int areaLightCount = 0;
	uint32_t skyTextureId = 0;
};

struct GPUInstance {
	RT64_INSTANCE *instance = nullptr;
	RT64_MATRIX4 transform;
};

struct GPUMesh {
	RT64_MESH *mesh = nullptr;
	float *deltaVertexBuffer = nullptr;
	uint64_t deltaVertexBufferSize = 0;
	uint64_t vertexBufferHash = 0;
	uint32_t vertexCount = 0;
	uint32_t vertexStride = 0;
	uint32_t indexCount = 0;
	bool raytrace = false;
	bool inUse = false;
	int staticFrames = 0;
};

struct GPUDisplayList {
	std::vector<GPUInstance> instances;
	std::vector<GPUMesh> meshes;
	int drawCount = 0;
};

struct GPUTexture {
	RT64_TEXTURE *texture = nullptr;
	uint64_t hash = 0;
};

struct UploadTexture {
	RT64_TEXTURE_DESC desc;
	uint32_t key;
	uint64_t hash;
};

//	Convention of bits for different lights.
//		1 	- Directional Tier A
//		2 	- Directional Tier B
//		4 	- Stage Tier A 
//		8 	- Stage Tier B
//		16 	- Objects Tier A
//		32 	- Objects Tier B
//		64 	- Particles Tier A
//		128 - Particles Tier B

struct RT64Context {
	// Window data.
	HWND hwnd = NULL;
	bool isFullScreen = false;
	bool lastMaximizedState = false;
	bool useVsync = true;
	bool cursorVisible = true;
	bool windowActive = true;
	RECT lastWindowRect;
	
	// Mouselook support.
	bool mouselookEnabled = false;
	int deltaMouseX = 0;
	int deltaMouseY = 0;
	int mouseButtons = 0;

	// Game data.
	RT64_MATERIAL defaultMaterial;
	RT64_TEXTURE *blankTexture = nullptr;
	AreaLighting levelAreaLighting[MAX_LEVELS][MAX_AREAS];
	std::mutex levelAreaLightingMutex;
	std::unordered_map<void *, std::string> geoLayoutNameMap;
	std::map<std::string, void *> nameGeoLayoutMap;
	std::unordered_map<void *, RecordedMod *> geoLayoutMods;
	std::unordered_map<uint64_t, std::string> texNameMap;
	std::map<std::string, uint64_t> nameTexMap;
	std::unordered_map<uint64_t, RecordedMod *> texMods;
	std::mutex texModsMutex;
	std::map<uint64_t, uint64_t> texHashAliasMap;
	std::map<uint64_t, std::vector<uint64_t>> texHashAliasesMap;
	std::unordered_map<uint32_t, uint64_t> textureHashIdMap;
	
	// Runtime data.
	std::unordered_map<uint32_t, RecordedTexture> textures;
	std::unordered_map<uint32_t, ShaderProgram *> shaderPrograms;
	std::mutex shaderProgramsMutex;
	std::unordered_map<void *, RecordedMod *> graphNodeMods;

	// Render thread.
	RT64_LIBRARY lib;
	RT64_DEVICE *device = nullptr;
	RT64_SCENE *scene = nullptr;
	RT64_VIEW *view = nullptr;
	std::thread *renderThread = nullptr;
	RT64_INSPECTOR *renderInspector = nullptr;
	std::vector<std::string> renderInspectorMessages;
	std::mutex renderInspectorMutex;
	GameFrame frames[MAX_RENDER_FRAMES];
	int CPUFrameIndex = 0;
	int GPUFrameIndex = -1;
	int BarrierFrameIndex = -1;
	std::unordered_map<uint32_t, GPUDisplayList> GPUDisplayLists;
	std::unordered_map<uint64_t, GPUMesh> GPUStaticMeshes;
	std::unordered_map<uint64_t, GPUMesh> GPUDynamicRtMeshes;
	std::unordered_map<uint64_t, GPUMesh> GPUDynamicRasterMeshes;
	std::unordered_map<uint32_t, GPUTexture> GPUTextures;
	std::mutex renderFrameIndexMutex;
	std::queue<UploadTexture> textureUploadQueue;
	std::mutex textureUploadQueueMutex;
	RT64_VIEW_DESC renderViewDesc;
	bool renderViewDescChanged = false;
	std::mutex renderViewDescMutex;
	RT64_LIGHT renderLights[MAX_LIGHTS];
    unsigned int renderLightCount = 0;
	unsigned int staticMeshesDrawn = 0;
	unsigned int dynamicMeshesDrawn = 0;
	unsigned int meshesCreated = 0;
	unsigned int meshesDestroyed = 0;
	std::atomic<bool> renderThreadRunning;
	std::atomic<bool> renderInspectorActive;
	unsigned int indexTriangleList[GFX_MAX_BUFFERED];

	// Ray picking data.
	bool pickTexture = false;
	bool pickTextureHighlight = false;
	uint64_t pickTextureHash = 0;
	std::mutex pickTextureMutex;

	// Matrices.
	RT64_MATRIX4 identityTransform;

	// Rendering state.
	int instancesDrawn = 0;
	int currentTile = 0;
    uint32_t currentTextureIds[2] = { 0, 0 };
	ShaderProgram *shaderProgram = nullptr;
	bool background = false;
	RT64_VECTOR3 fogColor;
	uint32_t skyTextureId;
	RT64_VECTOR3 skyDiffuseMultiplier;
	RT64_RECT scissorRect;
	RT64_RECT viewportRect;
	int16_t fogMul;
	int16_t fogOffset;
	RecordedMod *graphNodeMod;

	// Timing.
	unsigned int targetFPS = 30;
	LARGE_INTEGER StartingTime, EndingTime;
	LARGE_INTEGER Frequency;
	bool dropNextFrame;
	bool turboMode;
	std::atomic<bool> pauseMode;
	
	// Supported features.
	std::atomic<bool> dlssSupport;
	std::atomic<bool> fsrSupport;
	std::atomic<bool> xessSupport;

	// Function pointers for game.
    void (*run_one_game_iter)(void);
    bool (*on_key_down)(int scancode);
    bool (*on_key_up)(int scancode);
    void (*on_all_keys_up)(void);
};

extern RT64Context RT64;

#endif
