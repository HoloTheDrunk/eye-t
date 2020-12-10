#include "main.h"
#include <gtk/gtk.h>

typedef struct BannerMenu
{
    GtkMenuBar *menu;
    GtkMenuItem *open;
    GtkMenuItem *about;
} BannerMenu;

typedef struct UserInterface
{
    // Main top-level window
    GtkWindow *window;

    // Top menu
    BannerMenu banner_menu;

    // Images
    GtkImage *input_image;

    // Buttons
    GtkCheckButton *save_output_toggle;
    GtkCheckButton *spellcheck_toggle;
    GtkSpinButton *manual_rotation;
    GtkFileChooserButton *save_button;
    GtkButton *output_button;
} UserInterface;

gboolean on_input_image_button_release_event(UserInterface *ui)
{
    g_print("coucou sale %p\n", ui);
    return FALSE;
}

gboolean on_open_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UserInterface *ui = user_data;

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
            g_print("Loading file %s to image %p\n", filename, ui->input_image);
            gtk_image_set_from_file(ui->input_image, filename);
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
    GtkCheckButton *save_output_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "save_output_toggle"));
    GtkCheckButton *spellcheck_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "spellcheck_toggle"));
    GtkSpinButton *manual_rotation =
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "manual_rotation"));
    gtk_spin_button_set_range(manual_rotation, -180, 180);
    GtkFileChooserButton *save_button =
        GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "save_button"));
    GtkButton *output_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "manual_rotation"));

    UserInterface ui =
    {
        .window = window,

        .banner_menu =
        {
            .menu = menu,
            .open = open,
        },

        .input_image = input_image,

        .save_output_toggle = save_output_toggle,
        .spellcheck_toggle = spellcheck_toggle,
        .manual_rotation = manual_rotation,
        .save_button = save_button,
        .output_button = output_button,
    };

    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(open, "activate", G_CALLBACK(on_open_activate), &ui);

    gtk_main();

    return 0;
}
