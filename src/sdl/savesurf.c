#include "savesurf.h"

int png_colortype_from_surface(SDL_Surface *surface)
{
    int colortype = PNG_COLOR_MASK_COLOR; /* grayscale not supported */

    if (surface->format->palette)
        colortype |= PNG_COLOR_MASK_PALETTE;
    else if (surface->format->Amask)
        colortype |= PNG_COLOR_MASK_ALPHA;

    return colortype;
}

void png_user_warn(png_structp ctx, png_const_charp str)
{
    (void)(ctx);
    fprintf(stderr, "libpng: warning: %s\n", str);
}

void png_user_error(png_structp ctx, png_const_charp str)
{
    (void)(ctx);
    fprintf(stderr, "libpng: error: %s\n", str);
}



int png_save_surface(char *filename, SDL_Surface *surf)
{
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    int i, colortype;
    png_bytep *row_pointers;

    // Opening output file */
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        errx(-1, "fopen error");
        return -1;
    }

    // Initializing png structures and callbacks */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
            NULL, png_user_error, png_user_warn);
    if (png_ptr == NULL) {
        errx(-1, "png_create_write_struct error!\n");
        return -1;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        errx(-1, "png_create_info_struct error!\n");
        exit(-1);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        exit(-1);
    }

    png_init_io(png_ptr, fp);

    colortype = png_colortype_from_surface(surf);
    png_set_IHDR(png_ptr, info_ptr, surf->w, surf->h, 8, colortype,	PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    /* Writing the image */
    png_write_info(png_ptr, info_ptr);
    png_set_packing(png_ptr);

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*surf->h);
    for (i = 0; i < surf->h; i++)
        row_pointers[i] = (png_bytep)(Uint8 *)surf->pixels + i*surf->pitch;
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);

    /* Cleaning out... */
    free(row_pointers);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0;
}




/*
   int main(int argc, char **argv)
   {
   SDL_Surface *input_surf;
   char *input, *output, *str_ptr;
   int namelen;


//Parsing shell parameters
if (argc == 3) {
input = argv[1];
output = argv[2];
}
else if (argc == 2) {
input = argv[1];
str_ptr = strstr(argv[1], ".");
if (str_ptr == NULL)
namelen = strlen(argv[1]);
else
namelen = str_ptr - argv[1];
output = (char *)malloc(namelen + 5);
strncpy(output, argv[1], namelen);
strcat(output, ".png");
}
else {
printf("The correct syntax is: %s input [output]\n", argv[0]);
exit(-1);
}

// Initializing video subsystem
if (SDL_Init(SDL_INIT_VIDEO) < 0) {
printf("SDL_Init error: %s\n", SDL_GetError());
exit (-1);
}

// Calling SDL_Quit at exit
atexit(SDL_Quit);

printf("input file: %s\n", input);
printf("output file: %s\n", output);

//Opening input and output files
input_surf = IMG_Load(input);
if (input_surf == NULL) {
printf("IMG_Load error: %s\n", IMG_GetError());
exit(-1);
}

if(png_save_surface(output, input_surf) < 0)
exit(-1);

//Quitting
if (argc == 2)
free(output);
SDL_Quit();

return 0;
}*/
