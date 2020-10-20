#include "convolution_matrix.h"

SDL_Surface* convolute(SDL_Surface *surface, int matrix[][3]);

// The matrix is always 3x3
SDL_Surface* convolute(SDL_Surface *surface, int matrix[][3])
{
	int width = surface->w;
	int height = surface->h;

	SDL_Surface *output = new_rgb_surface(width, height);

    //Uint8 v;
	int validCells;

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
            Uint32 sum[3] = {0, 0, 0};
            //v = get_rgb(surface, x, y);
            validCells = 0;
			if(x > 0)
			{
				if(y > 0)
				{
					apply_kernel(get_rgb(surface,x-1,y-1), sum, matrix[0][0]);
					validCells += matrix[0][0];
				}
				if(y < height-1)
				{
					apply_kernel(get_rgb(surface,x-1,y+1), sum, matrix[0][2]);
					validCells += matrix[0][2];
				}
				apply_kernel(get_rgb(surface, x-1, y), sum, matrix[0][1]);
				validCells += matrix[0][1];
			}
			if(x < width-1)
			{
				if(y > 0)
				{
					apply_kernel(get_rgb(surface, x+1, y-1), sum, matrix[2][0]);
					validCells += matrix[2][0];
				}
				if(y < height-1)
				{
					apply_kernel(get_rgb(surface, x+1, y+1), sum, matrix[2][2]);
					validCells += matrix[2][2];
				}
				apply_kernel(get_rgb(surface, x+1, y), sum, matrix[2][1]);
				validCells += matrix[2][1];
			}
			if(y > 0)
			{
				apply_kernel(get_rgb(surface, x, y-1), sum, matrix[1][0]);
				validCells += matrix[1][0];
			}
			if(y < height-1)
			{
				apply_kernel(get_rgb(surface, x, y+1), sum, matrix[1][2]);
				validCells += matrix[1][2];
			}

			apply_kernel(get_rgb(surface, x, y), sum, matrix[1][1]);
			validCells += matrix[1][1];

			put_pixel(output, x, y, SDL_MapRGB(output->format,
                        sum[0]/validCells, 
                        sum[1]/validCells, 
                        sum[2]/validCells));
		}
	}

	return output;
}

// Adds two 3x3 matrices
int matrix_sum(int matrix[][3])
{
    int sum = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Does the calculation for a single pixel
Uint32* apply_kernel(Uint8 source[3], Uint32 destination[3], int kernel_value)
{
    for(int i = 0; i < 3; i++)
    {
        destination[i] += source[i] * kernel_value;
    }
    return destination;
}
