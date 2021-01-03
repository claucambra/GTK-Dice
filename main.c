#include <gtk/gtk.h>

int sides_dice = 6;
int num_dice = 2;

int dice_rack[1000];
int roll_history[10000];

static void
print_die(GtkWidget *widget, gpointer data) {
	g_print("%i\n", rand() % sides_dice + 1);
}

static void
// Activate function is called during initiation phase.
// Window is constructed within this function.
activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

	// Creates new GtkWindow and stores it in 'window' pointer
  window = gtk_application_window_new (app);
  // Below functions take a GtkWindow* pointer. But we're not casting 'window' with (GtkWindow*).
  // Pointer is cast with GTK_WINDOW macro, which will check if the pointer is an instance of GtkWindow class. 
  gtk_window_set_title (GTK_WINDOW (window), "GTK-Dice");
  gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
  
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);
  
  button = gtk_button_new_with_label ("Print Dice");
  g_signal_connect (button, "clicked", G_CALLBACK (print_die), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);
  
  // Shows window!
  gtk_widget_show_all (window);
}

int main (int argc, char **argv) { //Main function should be as small as possible.
  // GtkApplication is given a pointer to app.
  GtkApplication *app;
  int status;
  
	//Random num generator for dice, seed set as current time
	srand(time(NULL));

  // gtk_application_new creates a new GtkApplication instance.
  app = gtk_application_new ("org.claucambra.gtk-dice", G_APPLICATION_FLAGS_NONE);
  // This signal will be sent when g_application_run is called.
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  // Feeding argument pointers to g_application_run helps parse GTK specific args and remove them from the arg array, leaving you with args for your app
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
