#include "about.h"
#include "gtk/gtk.h"

void normvol_about(void) {
	GtkWidget *dialog, *button, *label;

	dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "About Normalize Volume "VERSION);
	gtk_container_border_width(GTK_CONTAINER(dialog), 5);
	label = gtk_label_new(
"Normalize Volume Plugin for XMMS\n\
by Baruch Even <baruch.even@writeme.com>\n\
Copyright (C) 2000 Baruch Even\n\
\n\
This program is free software; you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation; either version 2 of the License, or\n\
(at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program; if not, write to the Free Software\n\
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307  USA"
);

	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	button = gtk_button_new_with_label(" Close ");
	gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(dialog));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_widget_show(dialog);
	gtk_widget_grab_focus(button);
}
