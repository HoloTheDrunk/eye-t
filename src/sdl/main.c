#include "main.h"
#include <gtk/gtk.h>
#include "../neuralnetwork/NeuralNetwork.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

#define COUCOU(x) g_print("coucou %i\n", x);

typedef struct BannerMenu
{
    GtkMenuBar *menu;
    GtkMenuItem *open;
    GtkMenuItem *quit;
    GtkMenuItem *about;
} BannerMenu;

typedef struct UserInterface
{
    // Neural network
    Network *net;

    // Main top-level window
    GtkWindow *window;

    // Top menu
    BannerMenu banner_menu;

    // Input image
    char *input_filename;
    GtkEventBox *input_image_event_box;
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
    GtkTextBuffer *output_tree_text;
    GtkImage **processing_images;
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

void resize_to_fit(GtkImage *image, int size)
{
    // Resize image to fit
    const GdkPixbuf *pb = gtk_image_get_pixbuf(image);
    //g_print("%s\n", (pb == NULL ? "NULL" : "NOT NULL"));
    const int imgW = gdk_pixbuf_get_width(pb);
    const int imgH = gdk_pixbuf_get_height(pb);

    double ratio;
    int destW;
    int destH;

    if(imgW > imgH)
        ratio = size / (double)imgW;
    else
        ratio = size / (double)imgH;

    destW = ratio * imgW;
    destH = ratio * imgH;

    GdkPixbuf *result =
        gdk_pixbuf_scale_simple(pb, destW, destH, GDK_INTERP_BILINEAR);

    gtk_image_set_from_pixbuf(image, result);
}

void run_file_opener(UserInterface *ui)
{
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

    char *filename;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

            gtk_image_set_from_file(ui->input_image, filename);
            ui->input_filename = filename;

            resize_to_fit(ui->input_image, 360);

            break;
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

void on_open_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    UNUSED(menuitem);
    UserInterface *ui = user_data;

    run_file_opener(ui);
}

gboolean on_input_image_event_box_button_press_event(GtkWidget *widget,\
        GdkEvent *event, gpointer user_data)
{
    UNUSED(widget);
    UNUSED(event);
    UserInterface *ui = user_data;

    run_file_opener(ui);

    return TRUE;
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

void convert_step(int i, SDL_Surface *image_surface, UserInterface *ui)
{
    UNUSED(image_surface);
    char *filename;
    asprintf(&filename, "resources/steps/step_%i.png", i);
    // SAVE PNG IMAGE
    // save_image(image_surface, filename);
    gtk_image_set_from_file(ui->processing_images[i], filename);
    resize_to_fit(ui->processing_images[i], 132);
}

void on_output_button_clicked(GtkButton *button, gpointer user_data)
{
    UNUSED(button);
    UserInterface *ui = user_data;

    //COUCOU(1);
    // Do the stuff ///////////////////////////////////////////////////////////
    //// Image pre-processing
    SDL_Surface *image_surface = load_image(ui->input_filename);

    //COUCOU(2);
    greyscale(image_surface);
    // convert_step(0, image_surface, ui);

    //COUCOU(3);
    image_surface = Otsu_method(image_surface, 0);
    // convert_step(1, image_surface, ui);

    //COUCOU(4);
    if(gtk_toggle_button_get_active(\
                GTK_TOGGLE_BUTTON(ui->manual_rotation_toggle)))
        image_surface = SDL_RotationCentral(image_surface,\
                gtk_spin_button_get_value(ui->manual_rotation_amount));
    else
        image_surface = auto_rotate(image_surface);
    // convert_step(2, image_surface, ui);

    //COUCOU(5);
    image_surface = convolute(image_surface, gaussian_blur,\
            ARRAYLEN(gaussian_blur));
    // convert_step(3, image_surface, ui);

    image_surface = Otsu_method(image_surface, 0);
    // convert_step(4, image_surface, ui);

    fill_edges(image_surface, 0, 255);
    // convert_step(5, image_surface, ui);

    //COUCOU(6);
    //// Segmentation
    BinTree* bin = Segmentation(image_surface);

    //COUCOU(7);
    Resize_Leaves(bin, 28, 28);

    //MatBT_Print(bin);

    //COUCOU(8);
    LeavesBound(bin , ui->net);

    //COUCOU(9);
    check(bin);

    //COUCOU(10);
    //PrintTree(bin, 0);

    // char *output = (char *)calloc(1024, sizeof(char));
    // outputTree(bin, 0, output);
    // gtk_text_buffer_set_text(ui->output_tree_text, output, -1);
    // printf("%s", output);

    gtk_text_buffer_set_text(ui->output_text, Reconstruction(bin, ui->net), -1);

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->save_output_toggle)))
    {
        save_output(ui);
    }

    SDL_FreeSurface(image_surface);
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

    // Neural Network and training
    Network net;

    InitNetwork(&net,784);
    AddLayer(&net,100);
    AddLayer(&net,127);

    TrainNN(&net);

    // Main top-level window
    GtkWindow *window =
        GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.ocr"));

    // Top menu
    GtkMenuBar *menu =
        GTK_MENU_BAR(gtk_builder_get_object(builder, "menu"));

    // Input image
    GtkEventBox *input_image_event_box =
        GTK_EVENT_BOX(gtk_builder_get_object(builder, "input_image_event_box"));
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
    GtkTextBuffer *output_tree_text =
        GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "tree_output_text"));
    GtkImage *processing_images[6];
    for(int i = 0; i < 6; i++)
    {
        char *image_name;
        asprintf(&image_name, "process_step_%i", i+1);
        processing_images[i] =
            GTK_IMAGE(gtk_builder_get_object(builder, image_name));

        char *bmp_name;
        asprintf(&bmp_name, "./resources/steps/step_%i.bmp", i+1);
        gtk_image_set_from_file(processing_images[i], bmp_name);
        //resize_to_fit(processing_images[i], 132);
    }

    // Quit
    GtkMenuItem *quit =
        GTK_MENU_ITEM(gtk_builder_get_object(builder, "quit"));

    UserInterface ui =
    {
        .net = &net,

        // Main top-level window
        .window = window,

        // Top menu
        .banner_menu =
        {
            .menu = menu,
            .open = open,
            .quit = quit,
            .about = about,
        },

        // Input image
        .input_filename = malloc(256 * sizeof(char)),
        .input_image_event_box = input_image_event_box,
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
        .output_tree_text = output_tree_text,
        .processing_images = processing_images,
    };

    // Connects event handlers ////////////////////////////////////////////////
    //// Top-level window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(quit, "activate", G_CALLBACK(gtk_main_quit), NULL);

    //// Top Menu
    g_signal_connect(open, "activate", G_CALLBACK(on_open_activate), &ui);
    g_signal_connect(about, "activate", G_CALLBACK(on_about_activate), &ui);

    //// Input image
    g_signal_connect(GTK_WIDGET(input_image_event_box), "button-press-event",\
            G_CALLBACK(on_input_image_event_box_button_press_event), &ui);

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

    // Legacy: Print supported image formats.
    // GSList *formats = gdk_pixbuf_get_formats();
    // for(guint i = 0; i < g_slist_length(formats); i++)
    // {
    //     g_print("%s\n",
    //             gdk_pixbuf_format_get_name(g_slist_nth_data(formats, i)));
    // }

    gtk_main();

    free(ui.input_filename);

    return 0;
}
