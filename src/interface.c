/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

GtkWidget*
create_dialog_configuration (void)
{
  GtkWidget *dialog_configuration;
  GtkWidget *dialog_vbox1;
  GtkWidget *vbox1;
  GtkWidget *label1;
  GtkObject *adjustment;
  GtkWidget *hscale_level;
  GtkWidget *dialog_action_area1;
  GtkWidget *hbuttonbox1;
  GtkWidget *button_ok;
  GtkWidget *button_cancel;
  GtkWidget *button_apply;

  dialog_configuration = gtk_dialog_new ();
  gtk_widget_set_name (dialog_configuration, "dialog_configuration");
  gtk_object_set_data (GTK_OBJECT (dialog_configuration), "dialog_configuration", dialog_configuration);
  gtk_window_set_title (GTK_WINDOW (dialog_configuration), _("Normalize Volume Plugin Configurator"));
  GTK_WINDOW (dialog_configuration)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_policy (GTK_WINDOW (dialog_configuration), TRUE, TRUE, TRUE);

  dialog_vbox1 = GTK_DIALOG (dialog_configuration)->vbox;
  gtk_widget_set_name (dialog_vbox1, "dialog_vbox1");
  gtk_object_set_data (GTK_OBJECT (dialog_configuration), "dialog_vbox1", dialog_vbox1);
  gtk_widget_show (dialog_vbox1);

  vbox1 = gtk_vbox_new (FALSE, 3);
  gtk_widget_set_name (vbox1, "vbox1");
  gtk_widget_ref (vbox1);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "vbox1", vbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 4);

  label1 = gtk_label_new (_("Power level to adjust for"));
  gtk_widget_set_name (label1, "label1");
  gtk_widget_ref (label1);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "label1", label1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);

  adjustment = gtk_adjustment_new (0.25, 0, 1, 0.01, 0.1, 0);
  hscale_level = gtk_hscale_new (GTK_ADJUSTMENT (adjustment));
  gtk_widget_set_name (hscale_level, "hscale_level");
  gtk_widget_ref (hscale_level);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "hscale_level", hscale_level,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hscale_level);
  gtk_box_pack_start (GTK_BOX (vbox1), hscale_level, TRUE, TRUE, 0);
  gtk_scale_set_digits (GTK_SCALE (hscale_level), 2);

  dialog_action_area1 = GTK_DIALOG (dialog_configuration)->action_area;
  gtk_widget_set_name (dialog_action_area1, "dialog_action_area1");
  gtk_object_set_data (GTK_OBJECT (dialog_configuration), "dialog_action_area1", dialog_action_area1);
  gtk_widget_show (dialog_action_area1);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area1), 10);

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonbox1, "hbuttonbox1");
  gtk_widget_ref (hbuttonbox1);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "hbuttonbox1", hbuttonbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_start (GTK_BOX (dialog_action_area1), hbuttonbox1, TRUE, TRUE, 0);

  button_ok = gtk_button_new_with_label (_("OK"));
  gtk_widget_set_name (button_ok, "button_ok");
  gtk_widget_ref (button_ok);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "button_ok", button_ok,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_ok);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), button_ok);
  GTK_WIDGET_SET_FLAGS (button_ok, GTK_CAN_DEFAULT);

  button_cancel = gtk_button_new_with_label (_("Cancel"));
  gtk_widget_set_name (button_cancel, "button_cancel");
  gtk_widget_ref (button_cancel);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "button_cancel", button_cancel,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_cancel);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), button_cancel);
  GTK_WIDGET_SET_FLAGS (button_cancel, GTK_CAN_DEFAULT);

  button_apply = gtk_button_new_with_label (_("Apply"));
  gtk_widget_set_name (button_apply, "button_apply");
  gtk_widget_ref (button_apply);
  gtk_object_set_data_full (GTK_OBJECT (dialog_configuration), "button_apply", button_apply,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_apply);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), button_apply);
  GTK_WIDGET_SET_FLAGS (button_apply, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (dialog_configuration), "hide",
                      GTK_SIGNAL_FUNC (gtk_widget_destroy),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_ok), "clicked",
                      GTK_SIGNAL_FUNC (on_button_ok_clicked),
                      &GTK_ADJUSTMENT(adjustment)->value);
  gtk_signal_connect (GTK_OBJECT (button_cancel), "clicked",
                      GTK_SIGNAL_FUNC (on_button_cancel_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_apply), "clicked",
                      GTK_SIGNAL_FUNC (on_button_apply_clicked),
                      &GTK_ADJUSTMENT(adjustment)->value);

  return dialog_configuration;
}

