#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "cfg.h"

static double temp_normalize_level = -1.0;
static double temp_silence_level = -1.0;
static double temp_max_mult = -1.0;

static void
volnorm_prefs_value_changed(GtkAdjustment * adj, gpointer user_data)
{
	double value = GTK_ADJUSTMENT(adj)->value;

	switch (GPOINTER_TO_INT(user_data)) {
		case 1:
			temp_normalize_level = value;
			break;
			
		case 2:
			temp_silence_level = value;
			break;

		case 3:
			temp_max_mult = value;
			break;
		
		default:
			printf("ERROR in preferences dialog callback!\n");
	}

	if (temp_normalize_level < 0.0)
		temp_normalize_level = normalize_level;
	if (temp_silence_level < 0.0)
		temp_silence_level = silence_level;
	if (temp_max_mult < 0.0)
		temp_max_mult = max_mult;
}

static void 
volnorm_apply_changes(void)
{
	normalize_level = temp_normalize_level;
	silence_level = temp_silence_level;
	max_mult = temp_max_mult;
	
	write_config();
}

static void 
volnorm_hide_prefs_dialog(GtkWidget * widget)
{
	GtkWidget * dialog = lookup_widget(GTK_WIDGET(widget), "volnorm");
	g_assert(dialog != NULL);
	
	gtk_widget_hide(dialog);
}

void
on_button_ok_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	volnorm_apply_changes();
	volnorm_hide_prefs_dialog(GTK_WIDGET(button));
}


void
on_button_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	volnorm_apply_changes();
}


void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	volnorm_hide_prefs_dialog(GTK_WIDGET(button));
}

static void
volnorm_set_adjustment				   (GtkWidget * widget,
										char * adj_name,
										double adj_value,
										gint   adj_id)
{
	GtkWidget * hscale = NULL;
		
	hscale = lookup_widget(widget, adj_name);
	g_return_if_fail(hscale != NULL);
		
	{
		/* Get the adjustment out of the hscale, and set the value */
		GtkRange * range = GTK_RANGE(hscale);
		GtkAdjustment * adjustment = gtk_range_get_adjustment(range);

		/* Connect the signal */
		gtk_signal_connect(GTK_OBJECT(adjustment), "value-changed",
				GTK_SIGNAL_FUNC(volnorm_prefs_value_changed),
				GINT_TO_POINTER(adj_id));
		
		/* Change the value */
		gtk_adjustment_set_value(adjustment, adj_value);
	}
}

void
volnorm_dialog_prefs_update 		   (GtkWidget		*widget)
{
	volnorm_set_adjustment(widget, "hscale_target_power", 
			normalize_level, 1);
	volnorm_set_adjustment(widget, "hscale_silence_level",
			silence_level, 2);
	volnorm_set_adjustment(widget, "hscale_max_mult",
			max_mult, 3);
}
