#pragma once

#include <gtk/gtk.h>

#define TODO_APP_TYPE todo_app_get_type()
G_DECLARE_FINAL_TYPE(TodoApp, todo_app, TODO, APP, GtkApplication)

TodoApp *todo_app_new(void);
