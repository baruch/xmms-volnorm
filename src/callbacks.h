#include <gtk/gtk.h>


void
on_button_ok_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
volnorm_dialog_prefs_update 		   (GtkWidget		*widget);
