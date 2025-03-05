#include <gtk/gtk.h>

#include "todo_app.h"

int main(int argc, char *argv[])
{
	return g_application_run(G_APPLICATION(todo_app_new()), argc, argv);
}
