#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <gtk/gtk.h>
#include <xmms/plugin.h>
#include <xmms/xmmsctrl.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "normvol.h"
#include "about.h"
#include "cfg.h"
#include "smooth.h"
#include "interface.h"
#include "support.h"

static void normvol_init(void);
static void normvol_cleanup(void);
static int normvol_mod_samples(gpointer * d, gint length, AFormat afmt, gint srate, gint nch);

static void normvol_configure(void);

#define MAX_SRATE 50000
#define MAX_CHANNELS 2
#define BYTES_PS 2
#define BUFFER_SAMPLES (MAX_SRATE * MAX_DELAY / 1000)
#define BUFFER_SHORTS (BUFFER_SAMPLES * MAX_CHANNELS)
#define BUFFER_BYTES (BUFFER_SHORTS * BYTES_PS)

#define NO_GAIN 0.01
#define SMOOTH_SAMPLES 100

/* Keep the log on the values, and smooth them */
static smooth_t * smooth[MAX_CHANNELS];

static void calc_power_level(gpointer* d, gint length, gint nch);
static void adjust_gain(gpointer * d, gint length, double gain);

EffectPlugin normvol_ep =
{
	NULL,
	NULL,
	"Normalize Volume " VERSION,
	normvol_init,
	normvol_cleanup,
	normvol_about,	   /* about */
	normvol_configure, /* configure */
	normvol_mod_samples,
	NULL
};

EffectPlugin *get_eplugin_info(void)
{
	return &normvol_ep;
}

static void restart_smoothing(void) {
	gint channel = 0;

	for (channel = 0; channel < MAX_CHANNELS; ++channel) {
		if (smooth[channel] != NULL)
			SmoothDelete(smooth[channel]);

		smooth[channel] = SmoothNew(SMOOTH_SAMPLES);
	}
}

static gint song_changed(void) {
	/* These vars are used to detect a song change */
	static gint last_song = -1;
	static gint last_length = -1;

	gint song = -1;
	gint length = -1;

	/* Get the current song played and its total playing time */
	song = xmms_remote_get_playlist_pos(0);
	length = xmms_remote_get_playlist_time(0, song);

	/* If something is different, assume its a different song */
	if (song != last_song || length != last_length) {
		last_song = song;
		last_length = length;

		return TRUE;
	} else 
		return FALSE;
}

static void normvol_init(void) {
	read_config();

	/* Initialize the smoothing filter, set it to SMOOTH_SAMPLES samples */
	{
		gint channel = 0;
		for (channel = 0; channel < MAX_CHANNELS; ++channel)
			smooth[channel] = NULL;
		restart_smoothing();
	}
}

static void normvol_cleanup(void) {
	gint channel = 0;

	for (channel = 0; channel < MAX_CHANNELS; ++channel)
		SmoothDelete(smooth[channel]);
}

static void normvol_configure(void) 
{
	GtkWidget * dialog = NULL;
	GtkWidget * hscale = NULL;

	/* Create the dialog */
	dialog = create_dialog_configuration();
	g_assert(dialog);
	g_return_if_fail(dialog != NULL);
	
	/* Get the horizontal scale from inside the dialog */
	hscale = lookup_widget(dialog, "hscale_level");
	g_assert(hscale);
	g_return_if_fail(hscale != NULL);

	{
		/* Get the adjustment out of the hscale, and set the value */
		GtkRange * range = GTK_RANGE(hscale);
		GtkAdjustment * adjustment = gtk_range_get_adjustment(range);
		gtk_adjustment_set_value(adjustment, normalize_level);
	}

	/* Show the dialog */
	gtk_widget_show(dialog);
}

static int normvol_mod_samples(gpointer* d, gint length, AFormat afmt, gint srate, gint nch)
{
	double level = -1.0;

	/* Check only the last one, if it is allocated, most probably the others are
	 * too.
	 */
	if (smooth[MAX_CHANNELS-1] == NULL)
		return length;

	/* Make sure we can handle the format */
	if (!(afmt == FMT_S16_NE ||
	      (afmt == FMT_S16_LE && G_BYTE_ORDER == G_LITTLE_ENDIAN) ||
	      (afmt == FMT_S16_BE && G_BYTE_ORDER == G_BIG_ENDIAN)))
		return length;

	/* If there are too many channels do nothing. */
	if (nch > MAX_CHANNELS)
		return length;

	/* Check if the song changed */
	if (song_changed())
		restart_smoothing();
	
	/* Calculate power level for this sample */
	calc_power_level(d, length, nch);	

	/* Get the maximum level over all channels */
	{
		gint channel = 0;
		level = -1.0;

		for (channel = 0; channel < nch; ++channel) {
			double channel_level = SmoothGetMax(smooth[channel]);
			if (channel_level > level)
				level = channel_level;
		}

	}

	/* Only if the volume is higher than the silence level do something. */
	if (level > silence_level) {
		/* Calculate the gain for the level */
		double gain = normalize_level / sqrt(level);

		/* Make sure the gain is not above the maximum multiplier */
		if (gain > max_mult)
			gain = max_mult;

		/* Adjust the gain with the smoothed value */
		adjust_gain(d, length, gain);
		
		/* printf("Max level is %f, Gain is %f\n", level, gain); */
	}

	return length;
}

static void calc_power_level(gpointer* d, gint length, gint nch)
{
	gint channel = 0;
	gint i = 0;
	double sum[MAX_CHANNELS];

	gint16 * data = (gint16 *) *d;

	/* Zero the channel sum values */
	for (channel = 0; channel < nch; ++channel) {
		sum[channel] = 0.0;
	}

	/* Calculate the square sums for all channels at once 
	 * This will be do better memory access
	 */

	/* length is in bytes we use shorts */
	channel = 0;
	for (i = 0; i < length/2; ++i) {
		gint32 sample = *data;
		sum[channel] += sample * sample;
		
		++data;

		/* Switch to the next channel */
		++channel;
		channel = channel % nch;
	}
	
	/* Add the power level to the smoothing queue */
	{
		double channel_length = length/2;
		
		for (channel = 0; channel < nch; ++channel) {
			double level = sum[channel] / channel_length;
			
			/* Adjust the level to be between 0.0 -- 1.0 */
			level = level / (G_MAXSHORT * G_MAXSHORT);

			SmoothAddSample(smooth[channel], level);
		}
	}
}

static void adjust_gain(gpointer * d, gint length, double gain)
{
	/* We assume that this is correct, we check it before we get here */
	gint16 * data = (gint16 *) *d;
	gint i = 0;

	/* Change nothing if it won't be noticed */
	if (gain >= 1.0 - NO_GAIN && gain <= 1.0 + NO_GAIN)
		return;
	
	/* length is in bytes, we use two bytes per sample. */
	for (i = 0; i < length/2; ++i, ++data) {
		/* Convert sample to double */
		double sample = (double)*data;

		/* Multiply by gain */
		sample *= gain;

		/* Make sure it's within bounds and cast to gint16 */
		*data = (gint16) CLAMP(sample, G_MINSHORT, G_MAXSHORT);
	}
}
