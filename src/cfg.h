/* config.h */

#ifndef CONFIG_H
#define CONFIG_H

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

#endif
