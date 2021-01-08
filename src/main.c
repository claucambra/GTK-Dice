#include <gtk/gtk.h>
#include "dice.h"
#include "windows.h"

int main (int argc, char **argv) { //Main function should be as small as possible.
	GtkBuilder *builder;
	GObject *window;
	// GObject *button;
	GError *error = NULL;
	  
	gtk_init(&argc, &argv);
	  
	// Construct GtkBuilder instance and load UI description
	builder = gtk_builder_new(); 
	if (gtk_builder_add_from_file (builder, "ui/dice.ui", &error) == 0) {
		g_printerr ("Error loading dice.ui file: %s\n", error->message);
		g_clear_error (&error);
		return 1;
	} 
	  
	// Signal connections brought in from XML
	gtk_builder_connect_signals(builder, NULL);
	
	window = gtk_builder_get_object(builder, "main_window");
	
	// Otherwise, we can use these:
	// Connect signal handlers to constructed widgets
    // g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	// button = gtk_builder_get_object (builder, "roll_button");
	// g_signal_connect (button, "clicked", G_CALLBACK(roll_dice), NULL);
	
	// Connecting builder widgets to previously defined interactive elements
	total_display_label = GTK_WIDGET(gtk_builder_get_object(builder, "total_display"));
	list_display_label = GTK_WIDGET(gtk_builder_get_object(builder, "list_display"));
	sides_input_spin = GTK_WIDGET(gtk_builder_get_object(builder, "sides_input"));
	amount_input_spin = GTK_WIDGET(gtk_builder_get_object(builder, "amount_input"));
	stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack1"));
	stack_switcher = GTK_WIDGET(gtk_builder_get_object(builder, "rolls_stackswitcher"));
	text_view_scrollwindow = GTK_WIDGET(gtk_builder_get_object(builder, "rolls_text_scrollwindow"));
	icon_view = GTK_WIDGET(gtk_builder_get_object(builder, "icons_display"));
	
	// Set spin input numbers to default values
	gtk_spin_button_set_value((GtkSpinButton*)sides_input_spin, sides_dice);
	gtk_spin_button_set_value((GtkSpinButton*)amount_input_spin, amount_dice);
	
	//Random num generator for dice, seed set as current time
	srand(time(NULL));
	
	g_object_unref(builder); // Free builder from memory
	gtk_widget_show(GTK_WIDGET (window)); //Show the window 
	gtk_main();
	
	return 0;
}
