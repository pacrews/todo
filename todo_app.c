#include <gtk/gtk.h>

#include "todo_app.h"
#include "todo_win.h"

struct _TodoApp
{
	GtkApplication parent;
};

G_DEFINE_TYPE(TodoApp, todo_app, GTK_TYPE_APPLICATION);

static void todo_app_init(TodoApp *app)
{
}

static void todo_app_activate(GApplication *app)
{
	TodoAppWindow *win;

	win = todo_app_window_new(TODO_APP(app));
	gtk_window_present(GTK_WINDOW(win));
}

static void todo_app_class_init(TodoAppClass *class)
{
	G_APPLICATION_CLASS(class)->activate = todo_app_activate;
}

TodoApp *todo_app_new(void)
{
	return g_object_new(TODO_APP_TYPE, "application-id", "todo.pac", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
