#include "convolution_matrix.h"

SDL_Surface* convolute(SDL_Surface *surface, int matrix[][3]);

// The matrix is always 3x3
SDL_Surface* convolute(SDL_Surface *surface, int matrix[][3])
{
	int width = surface->w;
	int height = surface->h;

	SDL_Surface *output = new_rgb_surface(width, height);

	Uint32 sum;
	int validCells;
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			sum = 0;
			validCells = 0;
			if(x > 0)
			{
				if(y > 0)
				{
					sum += matrix[0][0] * get_pixel(surface, x-1, y-1);
					validCells++;
				}
				if(y < height-1)
				{
					sum += matrix[0][2] * get_pixel(surface, x-1, y+1);
					validCells++;
				}
				sum += matrix[0][1] * get_pixel(surface, x-1, y);
				validCells++;
			}
			if(x < width-1)
			{
				if(y > 0)
				{
					sum += matrix[2][0] * get_pixel(surface, x+1, y-1);
					validCells++;
				}
				if(y < height-1)
				{
					sum += matrix[2][2] * get_pixel(surface, x+1, y+1);
					validCells++;
				}
				sum += matrix[2][1] * get_pixel(surface, x+1, y);
				validCells++;
			}
			if(y > 0)
			{
				sum += matrix[1][0] * get_pixel(surface, x, y-1);
				validCells++;
			}
			if(y < height-1)
			{
				sum += matrix[1][2] * get_pixel(surface, x, y+1);
				validCells++;
			}

			sum += matrix[1][1] * get_pixel(surface, x, y);
			validCells++;

			put_pixel(output, x, y, sum/9);
		}
	}

	return output;
}
