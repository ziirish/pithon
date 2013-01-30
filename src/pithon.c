#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

/*
#define BPP 4
#define DEPTH 16
*/
const SDL_VideoInfo *infos;

void setpixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( screen->format, r, g, b );
  
    pixmem32 = (Uint32*) screen->pixels  + y + x;
    *pixmem32 = colour;
}

SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
    if(!Surface || !Width || !Height)
        return 0;
     
    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
 
    double    _stretch_factor_x = ((double)(Width)  / (double)(Surface->w)),
        _stretch_factor_y = ((double)(Height) / (double)(Surface->h));

    int y, x, o_y, o_x;
 
    for(y = 0; y < Surface->h; y++)
        for(x = 0; x < Surface->w; x++)
            for(o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    DrawPixel(_ret, (int)(_stretch_factor_x * x) + o_x,
                        (int)(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));
 
    return _ret;
}

void DrawScreen(SDL_Surface* screen, int h)
{ 
    int x, y, ytimesw;
  
    if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) return;
    }

    SDL_Surface *bg, *bg_resized;
    SDL_Rect bg_pos;

    bg_pos.x = 0;
    bg_pos.y = 0;

    bg = IMG_Load("logo.jpg");
//    bg_resized = ScaleSurface (bg, infos->current_w, infos->current_h);
    SDL_BlitSurface(bg, NULL, screen, &bg_pos);
/*
    for(y = 0; y < screen->h; y++ ) 
    {
        ytimesw = y*screen->pitch/BPP;
        for( x = 0; x < screen->w; x++ ) 
        {
            setpixel(screen, x, ytimesw, (x*x)/256+3*y+h, (y*y)/256+x+h, h);
        }
    }
*/
    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  
    SDL_Flip(screen); 
}


int main(int argc, char* argv[])
{
    SDL_Surface *screen, *background;
    SDL_Event event;
  
    int keypress = 0;
    int h=0; 
  
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;

    infos = SDL_GetVideoInfo();

    fprintf (stdout, "Screen resolution: %dx%d\nDepth: %d\n", infos->current_w, infos->current_h, infos->vfmt->BitsPerPixel);

    if (!(screen = SDL_SetVideoMode(infos->current_w, infos->current_h, infos->vfmt->BitsPerPixel, SDL_FULLSCREEN)))
    {
        SDL_Quit();
        return 1;
    }
  
    while(!keypress) 
    {
        DrawScreen(screen,h++);
        while(SDL_PollEvent(&event)) 
        {      
            switch (event.type) 
            {
                case SDL_QUIT:
                    keypress = 1;
                    break;
                case SDL_KEYDOWN:
                    keypress = 1;
                    break;
            }
        }
    }

    SDL_Quit();
  
    return 0;
}





