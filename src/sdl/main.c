#include "main.h"
#include <gtk/gtk.h>

typedef struct BannerMenu
{
    GtkMenuBar *menu;
    GtkMenuItem *open;
} BannerMenu;

typedef struct UserInterface
{
    // Main top-level window
    GtkWindow *window;

    // Auxilliary top-levels
    // GtkFileChooserDialog *file_chooser;

    // Top menu
    BannerMenu banner_menu;

    // Images
    GtkImage *input_image;
} UserInterface;

gboolean on_input_image_button_release_event(UserInterface *ui)
{
    g_print("coucou sale %p\n", ui);
    return FALSE;
}

gboolean on_open_activate(UserInterface *ui)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Open File", ui->window, 
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Open", GTK_RESPONSE_ACCEPT,
            NULL);

    const char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            ui->input_image = GTK_IMAGE(gtk_image_new_from_file(filename));
            break;
        case GTK_RESPONSE_CANCEL:
            g_print("cancelled\n");
            break;
        default:
            g_print("fck u\n");
            break;
    }

    g_print("coucou %p\n", ui->input_image);

    gtk_widget_destroy(dialog);

    return FALSE;
}

int main()
{
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Construct a GtkBuilder instance
    GtkBuilder *builder = gtk_builder_new();

    // Loads the UI description (exits if an error occurs)
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "ocr.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    GtkWindow *window =
        GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.ocr"));
    // GtkFileChooserDialog *file_chooser =
    GtkMenuBar *menu =
        GTK_MENU_BAR(gtk_builder_get_object(builder, "menu"));
    GtkMenuItem *open =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "open"));
    GtkImage *input_image =
        GTK_IMAGE(gtk_builder_get_object(builder, "input_image"));

    UserInterface ui =
    {
        .window = window,

        // .file_chooser = file_chooser,

        .banner_menu =
        {
            .menu = menu,
            .open = open,
        },

        .input_image = input_image,
    };

    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(open, "activate", G_CALLBACK(on_open_activate), &ui);

    gtk_main();

    return 0;
}



