#include "convolution_matrix.h"

// The matrix is always 3x3
//SDL_Surface* convolute(SDL_Surface *surface, int matrix[][3])
//{
//	int width = surface->w;
//	int height = surface->h;
//
//	SDL_Surface *output = new_rgb_surface(width, height);
//
//    //Uint8 v;
//	int validCells;
//
//	for(int y = 0; y < height; y++)
//	{
//		for(int x = 0; x < width; x++)
//		{
//            Uint32 sum[3] = {0, 0, 0};
//            //v = get_rgb(surface, x, y);
//            validCells = 0;
//			if(x > 0)
//			{
//				if(y > 0)
//				{
//					apply_kernel(get_rgb(surface,x-1,y-1), sum, matrix[0][0]);
//					validCells += matrix[0][0];
//				}
//				if(y < height-1)
//				{
//					apply_kernel(get_rgb(surface,x-1,y+1), sum, matrix[0][2]);
//					validCells += matrix[0][2];
//				}
//				apply_kernel(get_rgb(surface, x-1, y), sum, matrix[0][1]);
//				validCells += matrix[0][1];
//			}
//			if(x < width-1)
//			{
//				if(y > 0)
//				{
//					apply_kernel(get_rgb(surface, x+1, y-1), sum, matrix[2][0]);
//					validCells += matrix[2][0];
//				}
//				if(y < height-1)
//				{
//					apply_kernel(get_rgb(surface, x+1, y+1), sum, matrix[2][2]);
//					validCells += matrix[2][2];
//				}
//				apply_kernel(get_rgb(surface, x+1, y), sum, matrix[2][1]);
//				validCells += matrix[2][1];
//			}
//			if(y > 0)
//			{
//				apply_kernel(get_rgb(surface, x, y-1), sum, matrix[1][0]);
//				validCells += matrix[1][0];
//			}
//			if(y < height-1)
//			{
//				apply_kernel(get_rgb(surface, x, y+1), sum, matrix[1][2]);
//				validCells += matrix[1][2];
//			}
//
//			apply_kernel(get_rgb(surface, x, y), sum, matrix[1][1]);
//			validCells += matrix[1][1];
//
//			put_pixel(output, x, y, SDL_MapRGB(output->format,
//                        sum[0]/validCells,
//                        sum[1]/validCells,
//                        sum[2]/validCells));
//		}
//	}
//
//	return output;
//}

SDL_Surface* convolute(SDL_Surface *source, float mask[], size_t maskLen)
{
    size_t width = source->w;
    size_t height = source->h;
    size_t maskSize = isqrt(maskLen);

    SDL_Surface* output = new_rgb_surface(width, height);

    for(size_t j = 0; j < height; j++)
    {
        for(size_t i = 0; i < width; i++)
        {
            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;
            
            for(size_t l = 0; l < maskSize; l++)
            {
                for(size_t k = 0; k < maskSize; k++)
                {
                    if(i+k > 0 && i+k < width && j+l > 0 && j+l < height)
                    {
                        Uint8 *rgb = get_rgb(source, i+k, j+l);
                        r += rgb[0] * mask[k * maskSize + l];
                        g += rgb[1] * mask[k * maskSize + l];
                        b += rgb[2] * mask[k * maskSize + l];
                    }
                }
            }
            put_pixel(output, i, j, SDL_MapRGB(output->format, r, g, b));
        }
    }
    return output;
}


int isqrt(int n)
{
    int r = n;
    while(r*r > n)
    {
        r = (r + n/r)/2;
    }
    return r;
}


//// Calculates the sum of all the elements of a matrix
//int matrix_sum(int matrix[][])
//{
//    int sum = 0;
//    for(int i = 0; i < 3; i++)
//    {
//        for(int j = 0; j < 3; j++)
//        {
//            sum += matrix[i][j];
//        }
//    }
//    return sum;
//}
//
//// Does the calculation for a single pixel
//Uint32* apply_kernel(Uint8 source[3], 
//        Uint8 r, Uint8 g, Uint8 b, 
//        int kernel_value)
//{
//    r += source[0] * kernel_value;
//    g += source[1] * kernel_value;
//    b += source[2] * kernel_value;
//    for(int i = 0; i < 3; i++)
//    {
//        destination[i] += source[i] * kernel_value;
//    }
//    return destination;
//}
