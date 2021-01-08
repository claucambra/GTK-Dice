#ifndef WINDOWS_H_
#define WINDOWS_H_

extern GtkWidget *total_display_label;
extern GtkWidget *list_display_label;
extern GtkWidget *sides_input_spin;
extern GtkWidget *amount_input_spin;
extern GtkWidget *stack;
extern GtkWidget *stack_switcher;
extern GtkWidget *text_view_scrollwindow;
extern GtkWidget *icon_view;
extern GtkWidget *stats_display_label;

void sides_spin_handler();
void amount_spin_handler();
void roll_button_handler();
void clear_button_handler();
void stats_buton_handler();
void on_main_window_destroy();
void on_stats_window_destroy(GtkWindow *window);

#endif
