#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "cfg.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"

static void apply(gfloat value);
static void hide(GtkButton * widget);

void
on_button_ok_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	gfloat * value = (gfloat *) user_data;
	
	apply(*value);
	hide(button);
}


void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	hide(button);
}


void
on_button_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	gfloat * value = (gfloat *) user_data;
	
	apply(*value);
}

static void apply(gfloat value)
{
	normalize_level = value;

	write_config();
}

static void hide(GtkButton * widget)
{
	GtkWidget * dialog = lookup_widget(GTK_WIDGET(widget), "dialog_configuration");
	g_assert(dialog != NULL);
	
	gtk_widget_hide(dialog);
}
