#ifndef __DICEAPPWIN_H
#define __DICEAPPWIN_H

#include <gtk/gtk.h>
#include "diceapp.h"


#define DICE_APP_WINDOW_TYPE (dice_app_window_get_type ())
G_DECLARE_FINAL_TYPE (DiceAppWindow, dice_app_window, DICE, APP_WINDOW, GtkApplicationWindow)


DiceAppWindow *dice_app_window_new (DiceApp *app);


#endif /* __DICEAPPWIN_H */

