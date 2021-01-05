#include <gtk/gtk.h>

GtkWidget *total_display_label;

// Dice defaults
int sides_dice = 6;
int num_dice = 2;

int dice_rack[1000];
int roll_history[10000];

static void print_dice() {
	char output[1024];
	int i = 0;
	int total = 0;
	char list_buffer[50];
	while(dice_rack[i] != 0) {
		sprintf(list_buffer, "DICE %i: %i\n", i + 1, dice_rack[i]);
		g_strlcat(output, list_buffer, 1024); 
		total += dice_rack[i];
		i++;
	}

	memset(list_buffer, 0, sizeof list_buffer);
	
	// Printing total
	char charred_total[50];
	sprintf(charred_total, "<big><b>%i</b></big>", total);
	gtk_label_set_markup(GTK_LABEL(total_display_label), charred_total);
	memset(output, 0, sizeof output);
}

void roll_dice() {
	int roll_total = 0;
	
	memset(dice_rack, 0, sizeof dice_rack);
	for(int i = 0; i < num_dice; i++) {
		dice_rack[i] = rand() % sides_dice + 1;
		roll_total += dice_rack[i];
	}
	
	int i = 0;
	while(roll_history[i] != 0) {
		i++;
	}
	roll_history[i] = roll_total;
	
	print_dice();
}

// Called when window is closed
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
	g_signal_connect (button, "clicked", G_CALLBACK(roll_dice), NULL);
	
	total_display_label = GTK_WIDGET(gtk_builder_get_object(builder, "total_display"));
	
	//Random num generator for dice, seed set as current time
	srand(time(NULL));
	
	g_object_unref(builder); // Free builder from memory
	gtk_widget_show(GTK_WIDGET (window)); //Show the window 
	gtk_main();
	
	return 0;
}
