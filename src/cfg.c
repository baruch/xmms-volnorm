#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "cfg.h"
#include "xmms/configfile.h"

#include "stdio.h"

#define DEFAULT_LEVEL 0.25
#define DEFAULT_SILENCE 0.01
#define DEFAULT_MAX_MULT 5.0
#define DEFAULT_CUTOFF 13000.0
#define DEFAULT_DEGREE 2.0
#define DEFAULT_DO_COMPRESS 0

double normalize_level = DEFAULT_LEVEL;
double silence_level = DEFAULT_SILENCE;
double max_mult = DEFAULT_MAX_MULT;
double cutoff = DEFAULT_CUTOFF;
double degree = DEFAULT_DEGREE;
gboolean do_compress = DEFAULT_DO_COMPRESS;

void read_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();
#define CONFIG_READ_DOUBLE(id, var, def) \
	if (!xmms_cfg_read_double(config, "normvol", id, &var)) \
		var = def;

	/* Load the values, if it fails, set default value */
	if (!xmms_cfg_read_double(config, "normvol", "level", &normalize_level))
		normalize_level = DEFAULT_LEVEL;
	
	if (!xmms_cfg_read_double(config, "normvol", "silence", &silence_level))
		silence_level = DEFAULT_SILENCE;
	
	if (!xmms_cfg_read_double(config, "normvol", "maxmult", &max_mult))
		max_mult = DEFAULT_MAX_MULT;

	CONFIG_READ_DOUBLE("cutoff", cutoff, DEFAULT_CUTOFF);
	CONFIG_READ_DOUBLE("degree", degree, DEFAULT_DEGREE);

	if (!xmms_cfg_read_boolean(config, "normvol", "do_compress", &do_compress))
		do_compress = DEFAULT_DO_COMPRESS;

	xmms_cfg_free(config);
}

void write_config(void)
{
	ConfigFile * config = xmms_cfg_open_default_file();

	xmms_cfg_write_double(config, "normvol", "level", normalize_level);
	xmms_cfg_write_double(config, "normvol", "silence", silence_level);
	xmms_cfg_write_double(config, "normvol", "maxmult", max_mult);
	xmms_cfg_write_double(config, "normvol", "cutoff", cutoff);
	xmms_cfg_write_double(config, "normvol", "degree", degree);
	xmms_cfg_write_boolean(config, "normvol", "do_compress", do_compress);

	xmms_cfg_write_default_file(config);
	xmms_cfg_free(config);
}

void print_config(char const * msg)
{
	printf("%s\n", msg);
	printf("Normalize level: %0.2f\nSilence level: %0.2f\nMax Mult: %0.2f\n\n",
			normalize_level, silence_level, max_mult);
}
