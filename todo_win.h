#pragma once

#include <gtk/gtk.h>
#include "todo_app.h"

#define TODO_APP_WINDOW_TYPE todo_app_window_get_type()
G_DECLARE_FINAL_TYPE(TodoAppWindow, todo_app_window, TODO, APP_WINDOW, GtkApplicationWindow)

TodoAppWindow *todo_app_window_new(TodoApp *app);
