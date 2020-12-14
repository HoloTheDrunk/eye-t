#include "surface_binlist.h"

int* surface_binlist(SDL_Surface* picture)
{
	int width = picture->w;
	int height = picture->h;
	int* result = malloc((width*height)*sizeof(int));
	Uint8 r, g ,b;
	Uint32 pixel;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			pixel = get_pixel(picture, row, col);
			SDL_GetRGB(pixel, picture->format, &r, &g, &b);
			
			if(r == 0)
				result[row * width + col] = 1; //noir
			else
				result[row * width + col] = 0; //blanc
		}
	}

	return result;
}
