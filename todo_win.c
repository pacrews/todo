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

static void task_created_entry(GtkWidget *entry, GtkTextBuffer *text)
{
	GtkEntryBuffer *buf;

	buf = gtk_entry_get_buffer(GTK_ENTRY(entry));
	gtk_text_buffer_set_text(text, gtk_entry_buffer_get_text(buf), -1);

	gtk_widget_unparent(entry);
}

static void task_created_row(GtkWidget *row, GtkWidget *view)
{
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), view);
}

static void new_category(TodoAppWindow *win)
{
	GtkWidget *row;
	GtkWidget *entry;

	row = gtk_list_box_row_new();
	entry = gtk_entry_new();

	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), entry);
	gtk_widget_set_hexpand(row, false);
	gtk_widget_set_vexpand(row, false);
	gtk_list_box_append(GTK_LIST_BOX(win->cat_list), row);
	gtk_widget_set_hexpand(entry, false);
	gtk_widget_set_vexpand(entry, false);
}

static void new_task(TodoAppWindow *win)
{
	GtkWidget *row;
	GtkWidget *entry;
	GtkTextBuffer *text;
	GtkWidget *view;

	row = gtk_list_box_row_new();
	entry = gtk_entry_new();
	text = gtk_text_buffer_new(NULL);
	view = gtk_text_view_new_with_buffer(text);

	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), entry);
	gtk_widget_set_hexpand(row, true);
	gtk_widget_set_vexpand(row, false);
	gtk_list_box_append(GTK_LIST_BOX(win->task_list), row);
	gtk_widget_set_hexpand(entry, true);
	gtk_widget_set_vexpand(entry, false);

	struct cp_entry
	{
		GtkWidget *entry;
		GtkTextBuffer *text;
	};
	struct cp_entry *cp_ent = malloc(sizeof(*cp_ent));
	cp_ent->entry = entry;
	cp_ent->text = text;

	struct cp_row
	{
		GtkWidget *row;
		GtkWidget *view; 
	};
	struct cp_row *cp_r = malloc(sizeof(*cp_r));
	cp_r->row = row;
	cp_r->view = view;

	g_signal_connect(entry, "activate", G_CALLBACK(task_created_entry), cp_ent);
	g_signal_connect(entry, "activate", G_CALLBACK(task_created_row), cp_r);
}

static void newcat_activated(GSimpleAction *action, GVariant *param, gpointer win)
{
	new_category(win);
}

static void newtask_activated(GSimpleAction *action, GVariant *param, gpointer win)
{
	new_task(win);
}

static GActionEntry win_entries[] =
{
	{ "newcategory", newcat_activated },
	{ "newtask", newtask_activated }
};

static void todo_app_window_init(TodoAppWindow *win)
{
	GtkBuilder *builder;
	GMenuModel *menu;

	gtk_widget_init_template(GTK_WIDGET(win));

	builder = gtk_builder_new_from_resource("/home/pc/coding/todo/new-menu.ui");
	menu = G_MENU_MODEL(gtk_builder_get_object(builder, "menu"));
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(win->newmenu), menu);
	g_object_unref(builder);
	
	g_action_map_add_action_entries(G_ACTION_MAP(win), win_entries, G_N_ELEMENTS(win_entries), win);
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
