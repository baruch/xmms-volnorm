#include "config.h"

#include "smooth.h"
#include "glib.h"
#include "cfg.h"

struct smooth_struct {
	double * data;
	double max;
	gint size;
	gint used;
	gint current;
};

smooth_t * SmoothNew(gint size)
{
	smooth_t * sm = g_malloc0(sizeof(smooth_t));
	if (sm == NULL)
		return NULL;

	sm->data = g_malloc0(size * sizeof(double));
	if (sm->data == NULL) {
		g_free(sm);
		return NULL;
	}

	sm->size = size;
	sm->current = sm->used = 0;
	sm->max = 0.0;
	return sm;
}

void SmoothDelete(smooth_t * del)
{
	if (del == NULL)
		return;

	if (del->data != NULL)
		g_free(del->data);
	
	g_free(del);
}

void SmoothAddSample(smooth_t * sm, double sample)
{
	if (sm == NULL)
		return;

	/* Put the sample in the buffer */
	sm->data[sm->current] = sample;
	
	/* Adjust the sample stats */
	++sm->current;
	
	if (sm->current > sm->used)
		++sm->used;

	if (sm->current >= sm->size)
		sm->current %= sm->size;

}

double SmoothGetMax(smooth_t * sm)
{
	if (sm == NULL)
		return -1.0;

	/* Calculate the smoothed value */
	{
		int i = 0;
		double smoothed = 0.0;

		for (i = 0; i < sm->used; ++i)
			smoothed += sm->data[i];
		smoothed = smoothed / sm->used;
	
		/* If we haven't filled the smoothing buffer, 
		 * dont save the max value. 
		 */
		if (sm->used < sm->size)
			/* Average (weighted appropriately) the smoothed with normalize level for the unknown */
			return (smoothed*sm->used + normalize_level*(sm->size - sm->used)) / sm->size;

		if (sm->max < smoothed)
			sm->max = smoothed;
	}

	return sm->max;
}
