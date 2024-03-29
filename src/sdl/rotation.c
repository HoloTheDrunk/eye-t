#include <SDL/SDL.h>
#include <math.h>

#include "rotation.h"
static Uint32 SDL_LirePixel(SDL_Surface* surface, int x, int y);

static void SDL_EcrirePixel(SDL_Surface* surface, int x, int y, Uint32 pixel);

inline Uint32 SDL_LirePixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:


            return *(Uint32 *)p;
        default:
            return 0;
    }

}


inline void SDL_EcrirePixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;


    switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:

            *(Uint32 *)p = pixel;
            break;
    }

}

SDL_Surface* SDL_RotationCentral(SDL_Surface* origine, float angle)
{
    SDL_Surface* destination;
    int i;
    int j;
    Uint32 couleur;
    int mx, my;
    int bx, by;
    float angle_radian;


    angle_radian = -angle * 3.14159 / 180.0;

    destination = SDL_CreateRGBSurface(SDL_HWSURFACE, origine->w, origine->h,
            origine->format->BitsPerPixel, origine->format->Rmask,
            origine->format->Gmask, origine->format->Bmask,
            origine->format->Amask);


    if(destination==NULL)
        return NULL;

    mx = origine->w/2;
    my = origine->h/2;

    for(j=0;j<origine->h;j++)
        for(i=0;i<origine->w;i++)
        {

            bx = (int) (cos(angle_radian) * (i-mx) + \
                    sin(angle_radian) * (j-my)) + mx;
            by = (int) (-sin(angle_radian) * (i-mx) + \
                    cos(angle_radian) * (j-my)) + my;
            if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
            {
                couleur = SDL_LirePixel(origine, bx, by);
                SDL_EcrirePixel(destination, i, j, couleur);
            }
        }

    return destination;
}

SDL_Surface* SDL_RotationCentralN(SDL_Surface* origine, float angle)
{
    SDL_Surface* destination;
    int i;
    int j;
    Uint32 couleur;
    int mx, my, mxdest, mydest;
    int bx, by;
    float angle_radian;
    float tcos;
    float tsin;
    double largeurdest;
    double hauteurdest;

    angle_radian = -angle * 3.14159 / 180.0;

    tcos = cos(angle_radian);
    tsin = sin(angle_radian);

    largeurdest=   ceil(origine->w * fabs(tcos) + origine->h * fabs(tsin)),
        hauteurdest=   ceil( origine->w * fabs(tsin) + origine->h * fabs(tcos)),


        destination = SDL_CreateRGBSurface(SDL_HWSURFACE, largeurdest, hauteurdest,
                origine->format->BitsPerPixel, origine->format->Rmask,
                origine->format->Gmask, origine->format->Bmask,
                origine->format->Amask);

    if(destination==NULL)
        return NULL;

    mxdest = destination->w/2.;
    mydest = destination->h/2.;
    mx = origine->w/2.;
    my = origine->h/2.;

    for(j=0;j<destination->h;j++)
        for(i=0;i<destination->w;i++)
        {


            bx = (ceil (tcos * (i-mxdest) + tsin * (j-mydest) + mx));
            by = (ceil (-tsin * (i-mxdest) + tcos * (j-mydest) + my));
            if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
            {
                couleur = SDL_LirePixel(origine, bx, by);
                SDL_EcrirePixel(destination, i, j, couleur);
            }
        }

    return destination;
}
