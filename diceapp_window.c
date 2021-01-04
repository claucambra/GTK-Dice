#include <gtk/gtk.h>

#include "diceapp.h"
#include "diceapp_window.h"

struct _DiceAppWindow {
	GtkApplicationWindow parent;
};


G_DEFINE_TYPE(DiceAppWindow, dice_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void dice_app_window_init (DiceAppWindow *win) {
	gtk_widget_init_template (GTK_WIDGET (win));
}

static void dice_app_window_class_init (DiceAppWindowClass *class) {
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/claucambra/gtk-dice/gtk-dice.ui");

}

DiceAppWindow *dice_app_window_new (DiceApp *app) {
	return g_object_new (DICE_APP_WINDOW_TYPE, "application", app, NULL);
}

