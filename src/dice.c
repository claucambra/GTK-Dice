#include <gtk/gtk.h>
#include "dice.h"
#include "windows.h"

// Dice defaults
int sides_dice = 6;
int amount_dice = 2;
int dice_rack[1000]; // Holds all roll values
int roll_history[10000]; // History of roll totals

void roll_dice() { // Called by roll button
	int roll_total = 0;
	
	memset(dice_rack, 0, sizeof dice_rack);
	for(int i = 0; i < amount_dice; i++) {
		dice_rack[i] = rand() % sides_dice + 1;
		roll_total += dice_rack[i];
	}
	
	int i = 0;
	while(roll_history[i] != 0) {
		i++;
	}
	roll_history[i] = roll_total;
}
