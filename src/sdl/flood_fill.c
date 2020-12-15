#include <stdio.h>
#include "flood_fill.h"

void flood_fill(SDL_Surface *surface, int x, int y, int oldcolor, int newcolor)
{
    if(get_rgb(surface, x, y)[0] == oldcolor)
    {
        put_pixel(surface, x, y, SDL_MapRGB(surface->format, 
                    newcolor, newcolor, newcolor));
        if(x < surface->w - 1)
            flood_fill(surface, x+1, y, oldcolor, newcolor);
        if(y < surface->h - 1)
            flood_fill(surface, x, y+1, oldcolor, newcolor);
        if(x > 0)
            flood_fill(surface, x-1, y, oldcolor, newcolor);
        if(y > 0)
            flood_fill(surface, x, y-1, oldcolor, newcolor);
    }
}

void fill_corners(SDL_Surface *surface, int oldcolor, int newcolor)
{
    flood_fill(surface, 0, 0, oldcolor, newcolor);
    flood_fill(surface, surface->w - 1, 0, oldcolor, newcolor);
    flood_fill(surface, 0, surface->h - 1, oldcolor, newcolor);
    flood_fill(surface, surface->w, surface->h, oldcolor, newcolor);
}

void fill_edges(SDL_Surface *surface, int oldcolor, int newcolor)
{
    for(int i = 0; i < surface->w; i++)
    {
        if(get_v(surface, i, 0) == oldcolor)
            flood_fill(surface, i, 0, oldcolor, newcolor);
        if(get_v(surface, i, surface->h - 1) == oldcolor)
            flood_fill(surface, i, surface->h - 1, oldcolor, newcolor);
    }

    for(int j = 0; j < surface->h; j++)
    {
        if(get_v(surface, 0, j) == oldcolor)
            flood_fill(surface, 0, j, oldcolor, newcolor);
        if(get_v(surface, surface->w - 1, j) == oldcolor)
            flood_fill(surface, surface->w - 1, j, oldcolor, newcolor);
    }
}
