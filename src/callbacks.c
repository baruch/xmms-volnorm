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
static gboolean temp_do_compress = 0;
static double temp_cutoff = -1.0;
static double temp_degree = -1.0;

static void
volnorm_prefs_check_button_toggled(GtkToggleButton * cb, gpointer user_data)
{
	gboolean value = GTK_TOGGLE_BUTTON(cb)->active;

	switch (GPOINTER_TO_INT(user_data)) {
	case 6:
		temp_do_compress = value;
		break;
	
	default:
		printf("ERROR in preferences dialog callback!\n");
	}
}

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
	
		case 4:
			temp_cutoff = value;
			break;

		case 5:
			temp_degree = value;
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
	if (temp_degree < 0.0)
		temp_degree = degree;
	if (temp_cutoff < 0.0)
		temp_cutoff = cutoff;
}

static void 
volnorm_apply_changes(void)
{
	normalize_level = temp_normalize_level;
	silence_level = temp_silence_level;
	max_mult = temp_max_mult;
	degree = temp_degree;
	cutoff = temp_cutoff;
	do_compress = temp_do_compress;
	
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

static void
volnorm_set_checkbox				   (GtkWidget * widget,
										char * cb_name,
										gboolean cb_value,
										gint   cb_id)
{
	GtkWidget * cb = NULL;
		
	cb = lookup_widget(widget, cb_name);
	g_return_if_fail(cb != NULL);
		
	{
		/* Get the adjustment out of the hscale, and set the value */
		GtkToggleButton * check = GTK_TOGGLE_BUTTON(cb);

		/* Connect the signal */
		gtk_signal_connect(GTK_OBJECT(check), "toggled",
				GTK_SIGNAL_FUNC(volnorm_prefs_check_button_toggled),
				GINT_TO_POINTER(cb_id));
		
		/* Change the value */
		gtk_toggle_button_set_active(check, cb_value);
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
	
	volnorm_set_adjustment(widget, "hscale_cutoff",
			cutoff, 4);
	volnorm_set_adjustment(widget, "hscale_degree",
			degree, 5);
	
	volnorm_set_checkbox(widget, "check_compress",
			do_compress, 6);
}
