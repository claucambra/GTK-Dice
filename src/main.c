#include <gtk/gtk.h>

GtkWidget *total_display_label;

int sides_dice = 6;
int num_dice = 2;

int dice_rack[1000];
int roll_history[10000];

static void
print_die(GtkWidget *widget, gpointer data) {
	char output[10];
	sprintf(output, "%i\n", rand() % sides_dice + 1);
	gtk_label_set_text(GTK_LABEL(total_display_label), output);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

int main (int argc, char **argv) { //Main function should be as small as possible.
	GtkBuilder *builder;
	GObject *window;
	GObject *button;
	GError *error = NULL;
	  
	gtk_init(&argc, &argv);
	  
	// Construct GtkBuilder instance and load UI description
	builder = gtk_builder_new(); 
	if (gtk_builder_add_from_file (builder, "ui/dice.ui", &error) == 0) {
		g_printerr ("Error loading dice.ui file: %s\n", error->message);
		g_clear_error (&error);
		return 1;
	} 
	  
	// Connect signal handlers to constructed widgets
	window = gtk_builder_get_object(builder, "main_window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	button = gtk_builder_get_object (builder, "roll_button");
	g_signal_connect (button, "clicked", G_CALLBACK(print_die), NULL);
	
	total_display_label = GTK_WIDGET(gtk_builder_get_object(builder, "total_display"));
	
	//Random num generator for dice, seed set as current time
	srand(time(NULL));
	
	g_object_unref(builder); // Free builder from memory
	gtk_widget_show(GTK_WIDGET (window)); //Show the window 
	gtk_main();
	
	return 0;
}
