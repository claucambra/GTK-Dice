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
	// Setting GtkWidget pointer variables
  GtkWidget *window;
  GtkWidget *printdice_button;
  GtkWidget *test_button;
  GtkWidget *quit_button;
  GtkWidget *grid;

	// Creates new GtkWindow and stores it in 'window' pointer
  window = gtk_application_window_new (app);
  // Below functions take a GtkWindow* pointer. But we're not casting 'window' with (GtkWindow*).
  // Pointer is cast with GTK_WINDOW macro, which will check if the pointer is an instance of GtkWindow class. 
  gtk_window_set_title (GTK_WINDOW (window), "GTK-Dice");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  
  // Grid container that will pack our buttons
  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);
  
  // gtk_button_new_with_label returns a GtkButton
  printdice_button = gtk_button_new_with_label ("Print Dice");
  // g_signal_connect connects button to function print_die
  // Since print_die does not use any data as input, NULL is passed to it
  g_signal_connect (printdice_button, "clicked", G_CALLBACK (print_die), NULL);
  // place printdice_button in grid-cell(0,0), and make it fill just 1 cell horizontally and vertically
	gtk_grid_attach (GTK_GRID (grid), printdice_button, 0, 0, 1, 1);
	
	test_button = gtk_button_new_with_label ("Test button");
	gtk_grid_attach (GTK_GRID (grid), test_button, 1, 0, 1, 1);
	
	quit_button = gtk_button_new_with_label ("Quit");
	// g_signal_connect_swapped() allows you to specify what the callback function should take as parameter by letting you pass it as data. 
	// In this case the function being called back is gtk_widget_destroy() and the window pointer is passed to it.
	g_signal_connect_swapped (quit_button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_grid_attach (GTK_GRID (grid), quit_button, 0, 1, 2, 1);
  
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
  // g_object_unref frees the GtkApplication object from memory
  g_object_unref (app);

  return status;
}
