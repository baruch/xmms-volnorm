#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "cfg.h"
#include "xmms/configfile.h"

#define DEFAULT_LEVEL 0.25
#define DEFAULT_SILENCE 0.01
#define DEFAULT_MAX_MULT 15.0

double normalize_level = DEFAULT_LEVEL;
double silence_level = DEFAULT_SILENCE;
double max_mult = DEFAULT_MAX_MULT;

void read_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();

	/* Load the values, if it fails, set default value */
	if (!xmms_cfg_read_double(config, "normvol", "level", &normalize_level))
		normalize_level = DEFAULT_LEVEL;
	
	if (!xmms_cfg_read_double(config, "normvol", "silence", &silence_level))
		normalize_level = DEFAULT_SILENCE;
	
	if (!xmms_cfg_read_double(config, "normvol", "maxmult", &max_mult))
		normalize_level = DEFAULT_MAX_MULT;

	xmms_cfg_free(config);
}

void write_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();

	xmms_cfg_write_double(config, "normvol", "level", normalize_level);
	xmms_cfg_write_double(config, "normvol", "silence", silence_level);
	xmms_cfg_write_double(config, "normvol", "maxmult", max_mult);

	xmms_cfg_write_default_file(config);
	xmms_cfg_free(config);
}
