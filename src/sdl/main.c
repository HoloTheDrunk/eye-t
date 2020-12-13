#include "main.h"
#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

time_t start, stop;
clock_t ticks;
double value;

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

    // Input image
    GtkImage *input_image;

    // Buttons /////////////////////////////
    //// Options
    GtkCheckButton *save_output_toggle;
    GtkCheckButton *spellcheck_toggle;
    GtkCheckButton *manual_rotation_toggle;
    GtkSpinButton *manual_rotation_amount;

    //// Output
    GtkButton *save_button;
    GtkButton *output_button;
    ////////////////////////////////////////

    // Input
    GtkFileFilter *file_filter;

    // Output
    GtkTextBuffer *output_text;
} UserInterface;

SDL_Surface* Resize(SDL_Surface *img)
{
    SDL_Surface *dest =
        SDL_CreateRGBSurface(SDL_HWSURFACE,28,28,img->format->BitsPerPixel,\
                0,0,0,0);
    SDL_SoftStretch(img, NULL, dest, NULL);
    return dest;
}


SDL_Surface* redImage(int w,int h,SDL_Surface* src)
{
    SDL_Surface* ret =
        SDL_CreateRGBSurface(src->flags,w,h,src->format->BitsPerPixel,\
                src->format->Rmask, src->format->Gmask, src->format->Bmask,\
                src->format->Amask);
    if (!ret)
        return src;
    SDL_BlitSurface(src,NULL,ret,NULL);
    SDL_FreeSurface(src);
    SDL_Surface* surface = SDL_DisplayFormatAlpha(ret);
    SDL_FreeSurface(ret);
    return surface;
}

void on_open_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UNUSED(menuitem);
    UserInterface *ui = user_data;

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Open File", ui->window,
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Open", GTK_RESPONSE_ACCEPT,
            NULL);
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(filter);
    gtk_file_filter_set_name(filter, "Images (.png/.jpg/.jpeg/etc...)");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    const char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            gtk_image_set_from_file(ui->input_image, filename);

            // Resize image to fit
            const GdkPixbuf *pb =
                gtk_image_get_pixbuf(GTK_IMAGE(ui->input_image));
            const int imgW = gdk_pixbuf_get_width(pb);
            const int imgH = gdk_pixbuf_get_height(pb);

            double ratio;
            int destW;
            int destH;

            if(imgW > imgH)
                ratio = 360 / (double)imgW;
            else
                ratio = 360 / (double)imgH;

            destW = ratio * imgW;
            destH = ratio * imgH;

            GdkPixbuf *result =
                gdk_pixbuf_scale_simple(pb, destW, destH, GDK_INTERP_BILINEAR);

            gtk_image_set_from_pixbuf(ui->input_image, result);

            break;
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

void on_about_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UNUSED(menuitem);
    UNUSED(user_data);

    char *authors[] = {"Yassine DAMIRI <yassine.damiri@epita.fr>",\
        "Victor-Emmanuel PROVOST <victor-emmanuel.provost@epita.fr>",\
            "Raphaël DUHEN <raphael.duhen@epita.fr>",\
            "Param DAVE <param.dave@epita.fr>"};

    GdkPixbuf *logo =
        gdk_pixbuf_new_from_file("./resources/logo_small.png", NULL);
    gtk_show_about_dialog(\
            NULL,\
            "program-name", "Eye-T",\
            "logo", logo,\
            "title", "About Eye-T",\
            "comments", "Onii-san is watching you.",
            "version", "1.0.0",
            "license-type", GTK_LICENSE_MIT_X11,
            "authors", authors,
            NULL);
}

void on_save_button_clicked(GtkButton *button, gpointer user_data)
{
    UserInterface *ui = user_data;

    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Select File", ui->window, action,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Select", GTK_RESPONSE_ACCEPT,
            NULL);

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    gtk_file_chooser_set_current_name(chooser, "OCR_output");

    const char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

            gtk_button_set_label(button, filename);
            break;
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

void on_manual_rotation_amount_value_changed(GtkSpinButton *spin_button,\
        gpointer user_data)
{
    UNUSED(user_data);

    gtk_spin_button_set_value(spin_button,\
            (int)CLAMP(gtk_spin_button_get_value(spin_button), -180, 180));
}

void on_manual_rotation_toggle_toggled(GtkToggleButton *togglebutton,\
        gpointer user_data)
{
    UserInterface *ui = user_data;

    gtk_widget_set_sensitive(\
            GTK_WIDGET(ui->manual_rotation_amount),\
            gtk_toggle_button_get_active(togglebutton)\
            );
}

void on_save_output_toggle_toggled(GtkToggleButton *togglebutton,\
        gpointer user_data)
{
    UserInterface *ui = user_data;

    gtk_widget_set_sensitive(\
            GTK_WIDGET(ui->save_button),\
            gtk_toggle_button_get_active(togglebutton)\
            );
}

void save_output(UserInterface *ui)
{
    const char *filename = gtk_button_get_label(ui->save_button);
    if(!gtk_widget_get_sensitive(GTK_WIDGET(ui->save_button))
            || strcmp(filename, "Choose save location"))
    {
        FILE *fptr = fopen(filename, "w+");

        GtkTextIter start;
        GtkTextIter end;
        gtk_text_buffer_get_bounds(ui->output_text, &start, &end);

        gchar *text =
            gtk_text_buffer_get_text(ui->output_text, &start, &end, FALSE);

        fprintf(fptr, text);

        fclose(fptr);
    }
    else
    {
        GtkMessageDialog *dialog =
            GTK_MESSAGE_DIALOG(gtk_message_dialog_new_with_markup(\
                        ui->window,\
                        GTK_DIALOG_DESTROY_WITH_PARENT,\
                        GTK_MESSAGE_ERROR,\
                        GTK_BUTTONS_CLOSE,\
                        "<b>Please select a valid save location</b>"\
                        "<b> or disable saving.</b>"));

        gtk_dialog_run(GTK_DIALOG(dialog));

        gtk_widget_destroy(GTK_WIDGET(dialog));
    }
}

void on_output_button_clicked(GtkButton *button, gpointer user_data)
{
    UNUSED(button);
    UserInterface *ui = user_data;

    // Call OCR and build detected null-terminated text, then output
    // gtk_text_buffer_set_text(ui->output_text, [TEXT], -1);

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->save_output_toggle)))
    {
        save_output(ui);
    }
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

    // Main top-level window
    GtkWindow *window =
        GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.ocr"));

    // Top menu
    GtkMenuBar *menu =
        GTK_MENU_BAR(gtk_builder_get_object(builder, "menu"));

    // Input image
    GtkImage *input_image =
        GTK_IMAGE(gtk_builder_get_object(builder, "input_image"));

    // Input
    GtkFileFilter *file_filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(file_filter);

    // Buttons
    //// Input
    GtkMenuItem *open =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "open"));

    //// Options
    GtkCheckButton *save_output_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "save_output_toggle"));
    GtkCheckButton *spellcheck_toggle =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "spellcheck_toggle"));
    GtkCheckButton *manual_rotation_toggle =
        GTK_CHECK_BUTTON(\
                gtk_builder_get_object(\
                    builder,\
                    "manual_rotation_toggle"));
    GtkSpinButton *manual_rotation_amount =
        GTK_SPIN_BUTTON(\
                gtk_builder_get_object(\
                    builder,\
                    "manual_rotation_amount"));

    //// Output
    GtkButton *save_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "save_button"));
    GtkButton *output_button =
        GTK_BUTTON(gtk_builder_get_object(builder, "output_button"));

    // Annex
    GtkMenuItem *about =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "about"));

    // Output
    GtkTextBuffer *output_text =
        GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "output_text"));

    // Processing steps
    //GtkBox *processing_steps =
    //    GTK_BOX(gtk_builder_get_object(builder, "processing_steps"));

    UserInterface ui =
    {
        // Main top-level window
        .window = window,

        // Top menu
        .banner_menu =
        {
            .menu = menu,
            .open = open,
            .about = about,
        },

        // Input image
        .input_image = input_image,

        // Buttons
        //// Options
        .save_output_toggle = save_output_toggle,
        .spellcheck_toggle = spellcheck_toggle,
        .manual_rotation_toggle = manual_rotation_toggle,
        .manual_rotation_amount = manual_rotation_amount,

        //// Output
        .save_button = save_button,
        .output_button = output_button,

        // Input
        .file_filter = file_filter,

        // Output
        .output_text = output_text,
    };

    // Connects event handlers ////////////////////////////////////////////////
    //// Top-level window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //// Menu
    g_signal_connect(open, "activate", G_CALLBACK(on_open_activate), &ui);
    g_signal_connect(about, "activate", G_CALLBACK(on_about_activate), &ui);

    //// Options
    ////// Output
    g_signal_connect(save_output_toggle, "toggled",\
            G_CALLBACK(on_save_output_toggle_toggled), &ui);
    g_signal_connect(save_button, "clicked",\
            G_CALLBACK(on_save_button_clicked), &ui);
    g_signal_connect(output_button, "clicked",\
            G_CALLBACK(on_output_button_clicked), &ui);

    ////// Manual Rotation
    g_signal_connect(manual_rotation_toggle, "toggled",\
            G_CALLBACK(on_manual_rotation_toggle_toggled), &ui);
    g_signal_connect(manual_rotation_amount, "value-changed",\
            G_CALLBACK(on_manual_rotation_amount_value_changed), NULL);

    ///////////////////////////////////////////////////////////////////////////

    gtk_main();

    return 0;
}
