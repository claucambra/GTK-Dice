#include <gtk/gtk.h>

#include "diceapp.h"

int main (int argc, char **argv) { //Main function should be as small as possible.
	return g_application_run (G_APPLICATION (dice_app_new ()), argc, argv);
}
