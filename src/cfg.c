#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "cfg.h"
#include "xmms/configfile.h"

#define DEFAULT_LEVEL 0.25

double normalize_level = DEFAULT_LEVEL;

void read_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();

	if (!xmms_cfg_read_double(config, "normvol", "level", &normalize_level))
		normalize_level = DEFAULT_LEVEL;

	xmms_cfg_free(config);
}

void write_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();

	xmms_cfg_write_double(config, "normvol", "level", normalize_level);

	xmms_cfg_write_default_file(config);
	xmms_cfg_free(config);
}
