#include "elpch.h"
#include "Elastic/Utils/Utils.h"
#include "Elastic/Application.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Elastic {

	float Time::GetTime()
	{
		return glfwGetTime();
	}

	// std::string FileDialogs::OpenFile(const char* filter)
	// {
	// 	std::string filePath;

	// 	GtkWidget* dialog;
	// 	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	// 	gint res;

	// 	dialog = gtk_file_chooser_dialog_new("Open File",
	// 										 GTK_WINDOW(glfwGetX11Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow())),
	// 										 action,
	// 										 "_Cancel",
	// 										 GTK_RESPONSE_CANCEL,
	// 										 "_Open",
	// 										 GTK_RESPONSE_ACCEPT,
	// 										 NULL);

	// 	GtkFileFilter* fileFilter = gtk_file_filter_new();
	// 	gtk_file_filter_set_name(fileFilter, filter);
	// 	gtk_file_filter_add_pattern(fileFilter, filter);
	// 	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), fileFilter);

	// 	res = gtk_dialog_run(GTK_DIALOG(dialog));
	// 	if (res == GTK_RESPONSE_ACCEPT)
	// 	{
	// 		char* filename;
	// 		GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
	// 		filename = gtk_file_chooser_get_filename(chooser);
	// 		filePath = filename;
	// 		g_free(filename);
	// 	}

	// 	gtk_widget_destroy(dialog);

	// 	return filePath;
	// }

	// std::string FileDialogs::SaveFile(const char* filter)
	// {
	// 	std::string filePath;

	// 	GtkWidget* dialog;
	// 	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	// 	gint res;

	// 	dialog = gtk_file_chooser_dialog_new("Save File",
	// 										 GTK_WINDOW(glfwGetX11Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow())),
	// 										 action,
	// 										 "_Cancel",
	// 										 GTK_RESPONSE_CANCEL,
	// 										 "_Save",
	// 										 GTK_RESPONSE_ACCEPT,
	// 										 NULL);

	// 	GtkFileFilter* fileFilter = gtk_file_filter_new();
	// 	gtk_file_filter_set_name(fileFilter, filter);
	// 	gtk_file_filter_add_pattern(fileFilter, filter);
	// 	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), fileFilter);

	// 	res = gtk_dialog_run(GTK_DIALOG(dialog));
	// 	if (res == GTK_RESPONSE_ACCEPT)
	// 	{
	// 		char* filename;
	// 		GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
	// 		filename = gtk_file_chooser_get_filename(chooser);
	// 		filePath = filename;
	// 		g_free(filename);
	// 	}

	// 	gtk_widget_destroy(dialog);

	// 	return filePath;
	// }

}
