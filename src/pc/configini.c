/*
	libconfigini - an ini formatted configuration parser library
	Copyright (C) 2013-present Taner YILMAZ <taner44@gmail.com>

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	 1. Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.
	 2. Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.
	 3. Neither the name of copyright holders nor the names of its
		contributors may be used to endorse or promote products derived
		from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "configini.h"
#include "queue.h"


#define COMMENT_CHARS        "#"    /* default comment chars */
#define KEYVAL_SEP           '='    /* default key-val seperator character */
#define STR_TRUE             "1"    /* default string valu of true */
#define STR_FALSE            "0"    /* default string valu of false */

#define CONFIG_INIT_MAGIC    0x12F0ED1

#define UNUSED __attribute__((unused))

/**
 * \brief Configuration key-value
 */
typedef struct ConfigKeyValue
{
	char *key;
	char *value;
	TAILQ_ENTRY(ConfigKeyValue) next;
} ConfigKeyValue;

/**
 * \brief Configuration section
 */
typedef struct ConfigSection
{
	char *name;
	int numofkv;
	TAILQ_HEAD(, ConfigKeyValue) kv_list;
	TAILQ_ENTRY(ConfigSection) next;
} ConfigSection;

/**
 * \brief Configuration handle
 */
struct Config
{
	char *comment_chars;
	char keyval_sep;
	char *true_str;
	char *false_str;
	int  initnum;
	int  numofsect;
	TAILQ_HEAD(, ConfigSection) sect_list;
};




static int StrSafeCopy(char *dst, const char *src, int size)
{
	char *d = dst;
	const char *s = src;
	int n = size;

	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	if (n == 0) {
		if (size != 0)
			*d = '\0';
		while (*s++)
			;
	}

	return (s - src - 1);
}

static bool StrIsTypeOfTrue(const char *s)
{
	if ( !strcasecmp(s, "true") || !strcasecmp(s, "yes") || !strcasecmp(s, "1") )
		return true;
	return false;
}

static bool StrIsTypeOfFalse(const char *s)
{
	if ( !strcasecmp(s, "false") || !strcasecmp(s, "no") || !strcasecmp(s, "0") )
		return true;
	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


const char *ConfigRetToString(ConfigRet ret)
{
	switch(ret) {
		case CONFIG_OK:                return "OK";
		case CONFIG_ERR_FILE:          return "File IO error";
		case CONFIG_ERR_NO_SECTION:    return "No section";
		case CONFIG_ERR_NO_KEY:        return "No key";
		case CONFIG_ERR_MEMALLOC:      return "Memory allocation failed";
		case CONFIG_ERR_INVALID_PARAM: return "Invalid parameter";
		case CONFIG_ERR_INVALID_VALUE: return "Invalid value";
		case CONFIG_ERR_PARSING:       return "Parse error";
		default:                       return NULL;
	}
}

/**
 * \brief              ConfigSetCommentCharset() sets comment characters
 *
 * \param cfg          config handle
 * \param comment_ch   charaters to consider as comments
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigSetCommentCharset(Config *cfg, const char *comment_ch)
{
	char *p;

	if (!cfg || !comment_ch)
		return CONFIG_ERR_INVALID_PARAM;

	if ((p = strdup(comment_ch)) == NULL)
		return CONFIG_ERR_MEMALLOC;

	if (cfg->comment_chars)
		free(cfg->comment_chars);
	cfg->comment_chars = p;

	return CONFIG_OK;
}

/**
 * \brief              ConfigSetCommentCharset() sets comment characters
 *
 * \param cfg          config handle
 * \param ch           charater to consider as key-value seperator
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigSetKeyValSepChar(Config *cfg, char ch)
{
	if (!cfg)
		return CONFIG_ERR_INVALID_PARAM;

	cfg->keyval_sep = ch;

	return CONFIG_OK;
}

/**
 * \brief              ConfigSetCommentCharset() sets comment characters
 *
 * \param cfg          config handle
 * \param true_str     string value of boolean true (must be one of these: "true", "yes", "1")
 * \param false_str    string value of boolean false (must be one of these: "false", "no", "0")
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigSetBoolString(Config *cfg, const char *true_str, const char *false_str)
{
	char *t, *f;

	if ( !cfg ||
		 !true_str || !*true_str || !StrIsTypeOfTrue(true_str) ||
		 !false_str || !*false_str || !StrIsTypeOfFalse(false_str) )
		return CONFIG_ERR_INVALID_PARAM;

	if ((t = strdup(true_str)) == NULL)
		return CONFIG_ERR_MEMALLOC;

	if ((f = strdup(false_str)) == NULL) {
		free(t);
		return CONFIG_ERR_MEMALLOC;
	}

	if (cfg->true_str)
		free(cfg->true_str);
	if (cfg->false_str)
		free(cfg->false_str);

	cfg->true_str = t;
	cfg->false_str = f;

	return CONFIG_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief              ConfigGetSection() gets the requested section
 *
 * \param cfg          config handle to search in
 * \param section      section name to search for
 * \param sect         pointer to ConfigSection* searched for to save
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
static ConfigRet ConfigGetSection(const Config *cfg, const char *section, ConfigSection **sect)
{
	if (!cfg || !sect)
		return CONFIG_ERR_INVALID_PARAM;

	TAILQ_FOREACH(*sect, &cfg->sect_list, next) {
		if ( (section && (*sect)->name && !strcmp((*sect)->name, section)) ||
			 (!section && !(*sect)->name) ) {
			return CONFIG_OK;
		}
	}

	return CONFIG_ERR_NO_SECTION;
}

/**
 * \brief              Checks whether section exists
 *
 * \param cfg          config handle to search in
 * \param section      section name to search for
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
bool ConfigHasSection(const Config *cfg, const char *section)
{
	ConfigSection *sect = NULL;

	return ( (ConfigGetSection(cfg, section, &sect) == CONFIG_OK) ? true : false );
}

/**
 * \brief              ConfigGetKeyValue() gets the ConfigKeyValue *
 *
 * \param cfg          config handle
 * \param sect         section to search in
 * \param key          key to search for
 * \param kv           pointer to ConfigKeyValue* searched for to save
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
static ConfigRet ConfigGetKeyValue(UNUSED const Config *cfg, ConfigSection *sect, const char *key,
		ConfigKeyValue **kv)
{
	if (!sect || !key || !kv)
		return CONFIG_ERR_INVALID_PARAM;

	TAILQ_FOREACH(*kv, &sect->kv_list, next) {
		if (!strcmp((*kv)->key, key))
			return CONFIG_OK;
	}

	return CONFIG_ERR_NO_KEY;
}

/**
 * \brief            ConfigGetSectionCount() gets number of sections
 *
 * \param cfg        config handle to search in
 *
 * \return           Returns number of sections on success, -1 on failure.
 */
int ConfigGetSectionCount(const Config *cfg)
{
	if (!cfg)
		return -1;

	return (TAILQ_FIRST(&cfg->sect_list)->numofkv > 0 ? cfg->numofsect : cfg->numofsect - 1);
}

/**
 * \brief            ConfigGetKeyCount() gets number of keys
 *
 * \param cfg        config handle to search in
 * \param section    section name to search for
 *
 * \return           Returns number of keys on success, -1 on failure.
 */
int ConfigGetKeyCount(const Config *cfg, const char *section)
{
	ConfigSection *sect = NULL;

	if (!cfg)
		return -1;

	if (ConfigGetSection(cfg, section, &sect) != CONFIG_OK)
		return -1;

	return sect->numofkv;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief              ConfigReadString() reads a string value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param size         value buffer size
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadString(const Config *cfg, const char *section, const char *key,
		char *value, int size, const char *dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;

	if (!cfg || !key || !value || (size < 1))
		return CONFIG_ERR_INVALID_PARAM;

	*value = '\0';

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		if (dfl_value)
			StrSafeCopy(value, dfl_value, size);
		return ret;
	}

	StrSafeCopy(value, kv->value, size);

	return CONFIG_OK;
}

/**
 * \brief              ConfigReadInt() reads an integer value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadInt(const Config *cfg, const char *section, const char *key,
		int *value, int dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;
	char           *p    = NULL;

	if (!cfg || !key || !value)
		return  CONFIG_ERR_INVALID_PARAM;

	*value = dfl_value;

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		return ret;
	}

	*value = (int) strtol(kv->value, &p, 10);
	if (*p || (errno == ERANGE))
		return CONFIG_ERR_INVALID_VALUE;

	return CONFIG_OK;
}

/**
 * \brief              ConfigReadUnsignedInt() reads an unsigned integer value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadUnsignedInt(const Config *cfg, const char *section, const char *key,
		unsigned int *value, unsigned int dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;
	char           *p    = NULL;

	if (!cfg || !key || !value)
		return CONFIG_ERR_INVALID_PARAM;

	*value = dfl_value;

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		return ret;
	}

	*value = (unsigned int) strtoul(kv->value, &p, 10);
	if (*p || (errno == ERANGE))
		return CONFIG_ERR_INVALID_VALUE;

	return CONFIG_OK;
}

/**
 * \brief              ConfigReadFloat() reads a float value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadFloat(const Config *cfg, const char *section, const char *key,
		float *value, float dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;
	char           *p    = NULL;

	if (!cfg || !key || !value)
		return CONFIG_ERR_INVALID_PARAM;

	*value = dfl_value;

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		return ret;
	}

	*value = strtof(kv->value, &p);
	if (*p || (errno == ERANGE))
		return CONFIG_ERR_INVALID_VALUE;

	return CONFIG_OK;
}

/**
 * \brief              ConfigReadDouble() reads a double value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadDouble(const Config *cfg, const char *section, const char *key,
		double *value, double dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;
	char           *p    = NULL;

	if (!cfg || !key || !value)
		return CONFIG_ERR_INVALID_PARAM;

	*value = dfl_value;

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		return ret;
	}

	*value = strtod(kv->value, &p);
	if (*p || (errno == ERANGE))
		return CONFIG_ERR_INVALID_VALUE;

	return CONFIG_OK;
}

/**
 * \brief              ConfigReadBool() reads a boolean value from the cfg.
 *                     If any error occurs default value is copied to 'value' buffer and
 *                     returns reason. If key is optional and does not exists in config,
 *                     the 'value' is default value and return is CONFIG_ERR_NO_KEY
 *
 * \param cfg          config handle
 * \param section      section to search in
 * \param key          key to search for
 * \param value        value to save in
 * \param dfl_value    default value to copy back if any error occurs
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadBool(const Config *cfg, const char *section, const char *key,
		bool *value, bool dfl_value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;

	if (!cfg || !key || !value)
		return CONFIG_ERR_INVALID_PARAM;

	*value = dfl_value;

	if ( ((ret = ConfigGetSection(cfg, section, &sect)) != CONFIG_OK) ||
		 ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) != CONFIG_OK) ) {
		return ret;
	}

	if (StrIsTypeOfTrue(kv->value))
		*value = true;
	else if (StrIsTypeOfFalse(kv->value))
		*value = false;
	else
		return CONFIG_ERR_INVALID_VALUE;

	return CONFIG_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief              ConfigAddSection() creates a section in the cfg
 *
 * \param cfg          config handle
 * \param section      section to add
 * \param sect         pointer to added ConfigSection* or NULL if not needed
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
static ConfigRet ConfigAddSection(Config *cfg, const char *section, ConfigSection **sect)
{
	ConfigSection *_sect = NULL;
	ConfigRet      ret   = CONFIG_OK;

	if (!cfg)
		return CONFIG_ERR_INVALID_PARAM;

	if (!sect)
		sect = &_sect;

	if ((ret = ConfigGetSection(cfg, section, sect)) != CONFIG_ERR_NO_SECTION)
		return ret;

	*sect = calloc(1, sizeof(ConfigSection));
	if (*sect == NULL)
		return CONFIG_ERR_MEMALLOC;

	if (section) {
		if (((*sect)->name = strdup(section)) == NULL) {
			free(*sect);
			return CONFIG_ERR_MEMALLOC;
		}
	}

	TAILQ_INIT(&(*sect)->kv_list);
	TAILQ_INSERT_TAIL(&cfg->sect_list, *sect, next);
	++(cfg->numofsect);

	return CONFIG_OK;
}

/**
 * \brief              ConfigAddString() adds the key with string value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddString(Config *cfg, const char *section, const char *key, const char *value)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;
	const char     *p    = NULL;
	const char     *q    = NULL;

	if (!cfg || !key || !value)
		return CONFIG_ERR_INVALID_PARAM;

	if ((ret = ConfigAddSection(cfg, section, &sect)) != CONFIG_OK)
		return ret;

	switch (ret = ConfigGetKeyValue(cfg, sect, key, &kv)) {
		case CONFIG_OK:
			if (kv->value) {
				free(kv->value);
				kv->value = NULL;
			}
			break;

		case CONFIG_ERR_NO_KEY:
			if ((kv = calloc(1, sizeof(ConfigKeyValue))) == NULL)
				return CONFIG_ERR_MEMALLOC;
			if ((kv->key = strdup(key)) == NULL) {
				free(kv);
				return CONFIG_ERR_MEMALLOC;
			}
			TAILQ_INSERT_TAIL(&sect->kv_list, kv, next);
			++(sect->numofkv);
			break;

		default:
			return ret;
	}

	for (p = value; *p && isspace(*p); ++p)
		;
	for (q = p; *q && (*q != '\r') && (*q != '\n') && !strchr(cfg->comment_chars, *q); ++q)
		;
	while (*q && (q > p) && isspace(*(q - 1)))
		--q;

	kv->value = (char *) malloc(q - p + 1);
	if (kv->value == NULL) {
		TAILQ_REMOVE(&sect->kv_list, kv, next);
		--(sect->numofkv);
		free(kv->key);
		free(kv);
		return CONFIG_ERR_MEMALLOC;
	}
	memcpy(kv->value, p, q - p);
	kv->value[q - p] = '\0';

	return CONFIG_OK;
}

/**
 * \brief              ConfigAddInt() adds the key with integer value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddInt(Config *cfg, const char *section, const char *key, int value)
{
	char buf[64];

	snprintf(buf, sizeof(buf), "%d", value);

	return ConfigAddString(cfg, section, key, buf);
}

/**
 * \brief              ConfigAddUnsignedInt() adds the key with unsigned integer value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddUnsignedInt(Config *cfg, const char *section, const char *key, unsigned int value)
{
	char buf[64];

	snprintf(buf, sizeof(buf), "%u", value);

	return ConfigAddString(cfg, section, key, buf);
}

/**
 * \brief              ConfigAddFloat() adds the key with float value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddFloat(Config * cfg, const char *section, const char *key, float value)
{
	char buf[64];

	snprintf(buf, sizeof(buf), "%f", value);

	return ConfigAddString(cfg, section, key, buf);
}

/**
 * \brief              ConfigAddDouble() adds the key with double value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddDouble(Config *cfg, const char *section, const char *key, double value)
{
	char buf[64];

	snprintf(buf, sizeof(buf), "%f", value);

	return ConfigAddString(cfg, section, key, buf);
}

/**
 * \brief              ConfigAddBool() adds the key with blooean value to the cfg
 *
 * \param cfg          config handle
 * \param section      section to add in
 * \param key          key to save as
 * \param value        value to save as
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigAddBool(Config * cfg, const char *section, const char *key, bool value)
{
	return ConfigAddString(cfg, section, key, value ? cfg->true_str : cfg->false_str);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


static void _ConfigRemoveKey(ConfigSection *sect, ConfigKeyValue *kv)
{
	TAILQ_REMOVE(&sect->kv_list, kv, next);
	--(sect->numofkv);

	if (kv->key)
		free(kv->key);
	if (kv->value)
		free(kv->value);
	free(kv);
}

/**
 * \brief              ConfigRemoveKey() removes the key which exists under section from the cfg
 *
 * \param cfg          config handle
 * \param section      section to seach in
 * \param key          key to remove
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigRemoveKey(Config *cfg, const char *section, const char *key)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;
	ConfigRet       ret  = CONFIG_OK;

	if (!cfg || !key)
		return CONFIG_ERR_INVALID_PARAM;

	if ((ret = ConfigGetSection(cfg, section, &sect)) == CONFIG_OK) {
		if ((ret = ConfigGetKeyValue(cfg, sect, key, &kv)) == CONFIG_OK)
			_ConfigRemoveKey(sect, kv);
	}

	return ret;
}

static void _ConfigRemoveSection(Config *cfg, ConfigSection *sect)
{
	ConfigKeyValue *kv, *t_kv;

	if (!cfg || !sect)
		return;

	TAILQ_REMOVE(&cfg->sect_list, sect, next);
	--(cfg->numofsect);

	TAILQ_FOREACH_SAFE(kv, &sect->kv_list, next, t_kv) {
		_ConfigRemoveKey(sect, kv);
	}

	if (sect->name)
		free(sect->name);
	free(sect);
}

/**
 * \brief              ConfigRemoveSection() removes section from the cfgfile
 *
 * \param cfg          config handle
 * \param section      section to remove
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigRemoveSection(Config *cfg, const char *section)
{
	ConfigSection *sect = NULL;
	ConfigRet      ret  = CONFIG_OK;

	if (!cfg)
		return CONFIG_ERR_INVALID_PARAM;

	if ((ret = ConfigGetSection(cfg, section, &sect)) == CONFIG_OK)
		_ConfigRemoveSection(cfg, sect);

	return ret;
}

/**
 * \brief              ConfigNew() creates a cfg handle with
 *                     default section which has no section name
 *
 * \return             Config* handle on success, NULL on failure
 */
Config *ConfigNew()
{
	Config *cfg = NULL;

	cfg = calloc(1, sizeof(Config));
	if (cfg == NULL)
		return NULL;

	TAILQ_INIT(&cfg->sect_list);

	/* add default section */
	if (ConfigAddSection(cfg, CONFIG_SECTION_FLAT, NULL) != CONFIG_OK) {
		free(cfg);
		return NULL;
	}

	cfg->comment_chars = strdup(COMMENT_CHARS);
	cfg->keyval_sep = KEYVAL_SEP;
	cfg->true_str = strdup(STR_TRUE);
	cfg->false_str = strdup(STR_FALSE);
	cfg->initnum = CONFIG_INIT_MAGIC;

	return cfg;
}

/**
 * \brief          ConfigFree() frees the memory for the cfg handle
 *
 * \param cfg      config handle
 */
void ConfigFree(Config *cfg)
{
	ConfigSection *sect, *t_sect;

	if (cfg == NULL)
		return;

	TAILQ_FOREACH_SAFE(sect, &cfg->sect_list, next, t_sect) {
		_ConfigRemoveSection(cfg, sect);
	}

	if (cfg->comment_chars) free(cfg->comment_chars);
	if (cfg->true_str)      free(cfg->true_str);
	if (cfg->false_str)     free(cfg->false_str);

	free(cfg);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief              Gets section name on the buffer p
 *
 * \param cfg          config handle
 * \param p            read buffer
 * \param section      pointer address to section
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
static ConfigRet GetSectName(Config *cfg, char *p, char **section)
{
	char *q, *r;

	if (!cfg || !p || !*p || !section)
		return CONFIG_ERR_INVALID_PARAM;

	*section = NULL;

	/* get section name */
	while (*p && isspace(*p))
		++p;

	if (*p != '[')
		return CONFIG_ERR_PARSING;

	++p;
	while (*p && isspace(*p))
		++p;

	for (q = p;
		 *q && (*q != '\r') && (*q != '\n') && (*q != ']') && !strchr(cfg->comment_chars, *q);
		 ++q)
		;

	if (*q != ']')
		return CONFIG_ERR_PARSING;

	r = q + 1;

	while (*q && (q > p) && isspace(*(q - 1)))
		--q;

	if (q == p) /* section has no name */
		return CONFIG_ERR_PARSING;

	*q = '\0';
	*section = p;

	/* check rest of section */
	while (*r && isspace(*r))
		++r;

	/* there are unrecognized trailing data */
	if (*r && !strchr(cfg->comment_chars, *r))
		return CONFIG_ERR_PARSING;

	return CONFIG_OK;
}

/**
 * \brief              Gets key and value on the buffer p
 *
 * \param cfg          config handle
 * \param p            read buffer
 * \param key          pointer address to key
 * \param val          pointer address to value
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
static ConfigRet GetKeyVal(Config *cfg, char *p, char **key, char **val)
{
	char *q, *v;

	if (!cfg || !p || !*p || !key || !val)
		return CONFIG_ERR_INVALID_PARAM;

	*key = *val = NULL;

	/* get key */
	while (*p && isspace(*p))
		++p;

	for (q = p;
		 *q && (*q != '\r') && (*q != '\n') && (*q != cfg->keyval_sep) && !strchr(cfg->comment_chars, *q);
		 ++q)
		;

	if (*q != cfg->keyval_sep)
		return CONFIG_ERR_PARSING;

	v = q + 1;

	while (*q && (q > p) && isspace(*(q - 1)))
		--q;

	if (q == p) /* no key name */
		return CONFIG_ERR_PARSING;

	*q = '\0';
	*key = p;

	/* get value */
	while (*v && isspace(*v))
		++v;

	for (q = v;
		 *q && (*q != '\r') && (*q != '\n') && !strchr(cfg->comment_chars, *q);
		 ++q)
		;

	while (*q && (q > v) && isspace(*(q - 1)))
		--q;

	if (q == v) /* no value */
		return CONFIG_ERR_INVALID_VALUE;

	*q = '\0';
	*val = v;

	return CONFIG_OK;
}

/**
 * \brief              ConfigRead() reads the stream and populates the entire content to cfg handle
 *
 * \param fp           FILE handle to read
 * \param cfg          pointer to config handle.
 *                     If not NULL a handle created with ConfigNew() must be given.
 *                     If cfg is NULL a new one is created and saved to cfg.
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigRead(FILE *fp, Config **cfg)
{
	ConfigSection *sect    = NULL;
	char          *p       = NULL;
	char          *section = NULL;
	char          *key     = NULL;
	char          *val     = NULL;
	char           buf[4096];
	Config        *_cfg    = NULL;
	bool           newcfg  = false;
	ConfigRet      ret     = CONFIG_OK;

	if ( !fp || !cfg || (*cfg && ((*cfg)->initnum != CONFIG_INIT_MAGIC)) )
		return CONFIG_ERR_INVALID_PARAM;

	if (*cfg == NULL) {
		_cfg = ConfigNew();
		if (_cfg == NULL)
			return CONFIG_ERR_MEMALLOC;
		*cfg = _cfg;
		newcfg = true;
	}
	else
		_cfg = *cfg;

	while (!feof(fp)) {
		if (fgets(buf, sizeof(buf), fp) == NULL)
			continue;

		for (p = buf; *p && isspace(*p) ; ++p)
			;
		if (!*p || strchr(_cfg->comment_chars, *p))
			continue;

		if (*p == '[') {
			if ((ret = GetSectName(_cfg, p, &section)) != CONFIG_OK)
				goto error;

			if ((ret = ConfigAddSection(_cfg, section, &sect)) != CONFIG_OK)
				goto error;
		}
		else {
			if ((ret = GetKeyVal(_cfg, p, &key, &val)) != CONFIG_OK)
				goto error;
			if (!sect) 
				goto error;
			if ((ret = ConfigAddString(_cfg, sect->name, key, val)) != CONFIG_OK)
				goto error;
		}
	}

	return CONFIG_OK;

error:
	if (newcfg) {
		ConfigFree(_cfg);
		*cfg = NULL;
	}

	return ret;
}

/**
 * \brief              ConfigReadFile() opens and reads the file and populates the
 *                     entire content to cfg handle
 *
 * \param filename     name of file to open and load
 * \param cfg          pointer to config handle.
 *                     If not NULL a handle created with ConfigNew() must be given.
 *                     If cfg is NULL a new one is created and saved to cfg.
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigReadFile(const char *filename, Config **cfg)
{
	FILE      *fp  = NULL;
	ConfigRet  ret = CONFIG_OK;

	if ( !filename || !cfg || (*cfg && ((*cfg)->initnum != CONFIG_INIT_MAGIC)) )
		return CONFIG_ERR_INVALID_PARAM;

	if ((fp = fopen(filename, "r")) == NULL)
		return CONFIG_ERR_FILE;

	ret = ConfigRead(fp, cfg);

	fclose(fp);

	return ret;
}

/**
 * \brief              ConfigPrint() prints all cfg content to the stream
 *
 * \param cfg          config handle
 * \param stream       stream to print
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigPrint(const Config *cfg, FILE *stream)
{
	ConfigSection  *sect = NULL;
	ConfigKeyValue *kv   = NULL;

	if (!cfg || !stream)
		return CONFIG_ERR_INVALID_PARAM;

	TAILQ_FOREACH(sect, &cfg->sect_list, next) {
		if (sect->name)
			fprintf(stream, "[%s]\n", sect->name);

		TAILQ_FOREACH(kv, &sect->kv_list, next)
			fprintf(stream, "%s=%s\n", kv->key, kv->value);

		fprintf(stream, "\n");
	}

	return CONFIG_OK;
}

/**
 * \brief              ConfigPrintToFile() prints (saves) all cfg content to the file
 *
 * \param cfg          config handle
 * \param filename     filename to save in
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigPrintToFile(const Config *cfg, char *filename)
{
	FILE      *fp  = NULL;
	ConfigRet  ret = CONFIG_OK;

	if (!cfg || !filename)
		return CONFIG_ERR_INVALID_PARAM;

	if ((fp = fopen(filename, "wb")) == NULL)
		return CONFIG_ERR_FILE;

	ret = ConfigPrint(cfg, fp);

	fclose(fp);

	return ret;
}

/**
 * \brief              ConfigPrintSettings() prints settings to the stream
 *
 * \param cfg          config handle
 * \param stream       stream to print
 *
 * \return             Returns CONFIG_RET_OK as success, otherwise is an error.
 */
ConfigRet ConfigPrintSettings(const Config *cfg, FILE *stream)
{
	if (!cfg || !stream)
		return CONFIG_ERR_INVALID_PARAM;

	fprintf(stream, "\n");
	fprintf(stream, "Configuration settings: \n");
	fprintf(stream, "   Comment characters : %s\n", cfg->comment_chars);
	fprintf(stream, "   Key-Value seperator: %c\n", cfg->keyval_sep);
	fprintf(stream, "   True-False strings : %s-%s\n", cfg->true_str, cfg->false_str);
	fprintf(stream, "\n");

	return CONFIG_OK;
}

