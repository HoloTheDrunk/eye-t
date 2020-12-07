#include "main.h"
#include <gtk/gtk.h>

typedef struct BannerMenu
{
    GtkMenuBar *menu;
    GtkMenuItem *file;
} BannerMenu;

typedef struct UserInterface
{
    // Main window
    GtkWindow *window;

    // Top menu
    // BannerMenu *banner_menu;

    // Images
    GtkImage *input_image;
} UserInterface;

gboolean on_input_image_button_release_event(UserInterface *ui)
{
    g_print("coucou 1 %p", ui);
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
    // GtkMenuBar *menu =
    //     GTK_MENU_BAR(gtk_builder_get_object(builder, "menu"));
    // GtkMenuItem *file =
    //     GTK_MENU_ITEM(gtk_builder_get_object(builder, "file"));
    GtkImage *input_image =
        GTK_IMAGE(gtk_builder_get_object(builder, "input_image"));

    UserInterface ui =
    {
        .window = window,

        // .banner_menu =
        // {
        //     .menu = menu,
        //     .file = file,
        // }//,

        .input_image = input_image,
    };

    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(input_image, "button-release-event",
            G_CALLBACK(on_input_image_button_release_event), &ui);

    gtk_main();

    return 0;
}



/* Legacy CLI version
 * int main(int argc, char *argv[])
 * {
 *     if (argc < 2)
 *     {
 *         errx(0, "A file has to be specified.");
 *     }
 *
 *     SDL_Surface* image_surface = NULL;
 *     SDL_Surface* screen_surface = NULL;
 *
 *     init_sdl();
 *
 *     for(int i = 1; i < argc; i++)
 *     {
 *         if(argv[i][0] == '-' && argv[i][1] != '-')
 *         {
 *             switch(argv[i][1])
 *             {
 *                 case 'i':
 *                     if(i < argc-1)
 *                     {
 *                         image_surface = load_image(argv[i+1]);
 *                         i++;
 *                     }
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'o':
 *                     if(i < argc-1)
 *                     {
 *                         save_image(image_surface, argv[i+1]);
 *                         i++;
 *                     }
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'g':
 *                     if(image_surface != NULL)
 *                         greyscale(image_surface);
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'v':
 *                     if(image_surface != NULL)
 *                     {
 *                         greyscale(image_surface);
 *                         image_surface = Otsu_method(image_surface, 0);
 *                     }
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'r':
 *                     if(image_surface != NULL)
 *                         image_surface = auto_rotate(image_surface);
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'b':
 *                     if(image_surface != NULL)
 *                         image_surface = convolute(image_surface, gaussian_blur,
 *                                 ARRAYLEN(gaussian_blur));
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
 *                     break;
 *                 case 'e':
 *                     if(image_surface != NULL)
 *                         image_surface = convolute(image_surface, edge_detection,
 *                                 ARRAYLEN(edge_detection));
 *                     else
 *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
*                     break;
*                 case 'd':
*                     if(image_surface != NULL)
    *                         screen_surface = display_image(image_surface);
    *                     else
    *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
    *                     break;
    *                 case 's':
*                     if(image_surface != NULL)
    *                         SegmentationTest(image_surface);
    *                     else
    *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
    *                     break;
    *                 case 'c':
*                     if(image_surface != NULL)
    *                         fill_edges(image_surface, 0, 255);
    *                     else
    *                         errx(0, "-%c: Incorrect usage, check man.", argv[i][1]);
    *                     break;
    *                 default:
    *                     errx(1, "-%c: Invalid command, check man.", argv[i][1]);
    *             }
    *         }
    *
    * //        if(compare_strings(argv[i], "--dothething") == 1)
    * //        {
    * //            if(i < argc-1)
    * //            {
    * //                image_surface = load_image(argv[i+1]);
    * //                // Otsu (-v)
    * //                greyscale(image_surface);
    * //                image_surface = Otsu_method(image_surface, 0);
    * //                // Clean (-c)
    * //                fill_edges(image_surface, 0, 255);
    * //                // Auto-rotate (-r)
    * //                image_surface = Otsu_method(image_surface, 255);
    * //                image_surface = auto_rotate(image_surface);
    * //                image_surface = Otsu_method(image_surface, 0);
    * //                // Gaussian blur (-b)
    * //                image_surface = convolute(image_surface, gaussian_blur,
    * //                        ARRAYLEN(gaussian_blur));
    * //                fill_edges(image_surface, 0, 255);
    * //                i++;
    * //            }
    * //            else
    * //                errx(0, "--dothething: Incorrect usage, check man.");
    * //        }
    * //        if(compare_strings(argv[i], "--finishthething") == 1)
    * //        {
    * //            if(image_surface != NULL)
    * //            {
    * //                SegmentationTest(image_surface);
    * //                save_image(image_surface, "eye_t.bmp");
    * //                wait_for_keypressed();
    * //            }
    * //            else
    * //                errx(0, "--finishthething Incorrect usage, check man.");
    * //        }
    *     }
    *
*     if(image_surface != NULL)
    *         SDL_FreeSurface(image_surface);
*     if(screen_surface != NULL)
    *         SDL_FreeSurface(screen_surface);
    *
    *     return 0;
    * }
    */
