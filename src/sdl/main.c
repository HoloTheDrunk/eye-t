#include "image_load.h"
#include "convolution_matrix.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		errx(0, "A file has to be specified.");
	}

	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

	init_sdl();

	image_surface = load_image(argv[1]);
	screen_surface = display_image(image_surface);

	//int width = image_surface->w;
	//int height = image_surface->h;
	
	wait_for_keypressed();

	/*IMAGE TREATMENT*/


	/////////// LOOK HERE
	int gaussian_blur[3][3] = { 
		{ 0, 1, 0 },
		{ 1, 5, 1 },
		{ 0, 1, 0 } 
	};

	image_surface = convolute(image_surface, gaussian_blur);

	update_surface(screen_surface, image_surface);
	/////////// NOW LOOK AT FUNCTION TYPES ON THE LEFT THEN AT CLI

	//save_image(image_surface, "eye_t.bmp");

	wait_for_keypressed();

	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);


	return 0;
}
