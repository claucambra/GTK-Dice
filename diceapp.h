#ifndef __DICEAPP_H
#define __DICEAPP_H

#include <gtk/gtk.h>


#define DICE_APP_TYPE (dice_app_get_type ())
G_DECLARE_FINAL_TYPE (DiceApp, dice_app, DICE, APP, GtkApplication)


DiceApp *dice_app_new (void);
static void print_die();


#endif /* __DICEAPP_H */

