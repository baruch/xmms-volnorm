/* config.h */

#ifndef CFG_H
#define CFG_H

/**
 * Read the config data into the global variables.
 */
extern void read_config(void);

/**
 * Write the config data from the global variables.
 */
extern void write_config(void);

/** The level to normalize for */
extern double normalize_level;

/** The silence level, sound below this level is not adjusted. */
extern double silence_level;

/** Maximum multiplier to use. */
extern double max_mult;

#endif
