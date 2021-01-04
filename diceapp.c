#include <gtk/gtk.h>

#include "diceapp.h"
#include "diceapp_window.h"

int sides_dice = 6;
int num_dice = 2;

int dice_rack[1000];
int roll_history[10000];

static void print_die(GtkWidget *widget, gpointer data) {
	g_print("%i\n", rand() % sides_dice + 1);
}

struct _DiceApp {
	GtkApplication parent;
};

G_DEFINE_TYPE(DiceApp, dice_app, GTK_TYPE_APPLICATION);

static void dice_app_init (DiceApp *app) {
}

static void dice_app_startup (GApplication *app) {
	GtkBuilder *builder;
	GObject *window;
	GObject *button;
	GError *error = NULL;
	
	G_APPLICATION_CLASS (dice_app_parent_class)->startup (app);
	  
	// Construct GtkBuilder instance and load UI description
	builder = gtk_builder_new_from_resource ("/org/claucambra/gtk-dice/gtk-dice.ui"); 

	// Connect signal handlers to constructed widgets
	window = gtk_builder_get_object (builder, "window");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	button = gtk_builder_get_object (builder, "print_button");
	g_signal_connect (button, "clicked", G_CALLBACK(print_die), NULL);
	
	// button = gtk_builder_get_object (builder, "test_button");
	// g_signal_connect (button, "clicked", G_CALLBACK(), NULL);
	
	button = gtk_builder_get_object (builder, "quit_button");
	g_signal_connect (button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	
	//Random num generator for dice, seed set as current time
	srand(time(NULL));
	
	g_object_unref (builder);
}

static void dice_app_activate (GApplication *app) {
	DiceAppWindow *win;
	
	win = dice_app_window_new (DICE_APP (app));
	gtk_window_present (GTK_WINDOW (win));
}

static void dice_app_class_init (DiceAppClass *class) {
	// Overriding
	G_APPLICATION_CLASS (class)->startup = dice_app_startup;
	G_APPLICATION_CLASS (class)->activate = dice_app_activate;
}

DiceApp *dice_app_new (void) {
	return g_object_new (DICE_APP_TYPE, "application-id", "org.claucambra.gtk-dice", NULL);
}
