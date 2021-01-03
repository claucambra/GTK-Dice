#include <gtk/gtk.h>

static void
// Activate function is called during initiation phase.
// Window is constructed within this function.
activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;

	// Creates new GtkWindow and stores it in 'window' pointer
  window = gtk_application_window_new (app);
  // Below functions take a GtkWindow* pointer. But we're not casting 'window' with (GtkWindow*).
  // Pointer is cast with GTK_WINDOW macro, which will check if the pointer is an instance of GtkWindow class. 
  gtk_window_set_title (GTK_WINDOW (window), "GTK-Dice");
  gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
  // Shows window!
  gtk_widget_show_all (window);
}

int main (int argc, char **argv) { //Main function should be as small as possible.
  // GtkApplication is given a pointer to app.
  GtkApplication *app;
  int status;

  // gtk_application_new creates a new GtkApplication instance.
  app = gtk_application_new ("org.claucambra.gtk-dice", G_APPLICATION_FLAGS_NONE);
  // This signal will be sent when g_application_run is called.
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  // Feeding argument pointers to g_application_run helps parse GTK specific args and remove them from the arg array, leaving you with args for your app
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
