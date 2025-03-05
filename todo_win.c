#include <gtk/gtk.h>

#include "todo_app.h"
#include "todo_win.h"

struct _TodoAppWindow
{
	GtkApplicationWindow parent;

	GtkWidget *newmenu;
	GtkWidget *cat_list;
	GtkWidget *task_list;
};

G_DEFINE_TYPE(TodoAppWindow, todo_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void new_category(TodoAppWindow *win)
{
	GtkWidget *row;
	GtkWidget *entry;

	row = gtk_list_box_row_new();
	entry = gtk_entry_new();

	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), entry);
	gtk_list_box_append(GTK_LIST_BOX(win->cat_list), row);
}

static void new_category_cb(GObject *obj, GParamSpec *pspec, TodoAppWindow *win)
{
	new_category(win);
}

static void todo_app_window_init(TodoAppWindow *win)
{
	GtkBuilder *builder;
	GMenuModel *menu;

	gtk_widget_init_template(GTK_WIDGET(win));

	builder = gtk_builder_new_from_resource("/home/pc/coding/todo/new-menu.ui");
	menu = G_MENU_MODEL(gtk_builder_get_object(builder, "menu"));
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(win->newmenu), menu);
	g_object_unref(builder);

	g_signal_connect(win->cat_list, "notify::newcategory", G_CALLBACK(new_category_cb), win);
}

static void todo_app_window_class_init(TodoAppWindowClass *class)
{
	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/home/pc/coding/todo/window.ui");

	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), TodoAppWindow, newmenu);
	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), TodoAppWindow, cat_list);
	gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), TodoAppWindow, task_list);
}

TodoAppWindow *todo_app_window_new(TodoApp *app)
{
	return g_object_new(TODO_APP_WINDOW_TYPE, "application", app, NULL);
}
