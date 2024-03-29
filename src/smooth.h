/* smooth.h */

#ifndef SMOOTH_H
#define SMOOTH_H

#include <glib.h>

typedef struct smooth_struct smooth_t;

extern smooth_t * SmoothNew(gint size);
extern void SmoothDelete(smooth_t * del);
extern void SmoothAddSample(smooth_t * sm, double sample);
extern double SmoothGetMax(smooth_t * sm);

#endif
