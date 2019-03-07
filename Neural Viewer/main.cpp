#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#define NB_MAX_SON 10

using namespace std;

#include "SDL_Window.hpp"
#include <windows.h>

int main()
{

    SDL_Win win("nom",500,300,((COLOR){0xFF,0xFF,0xFF})) ;
    Sleep(4002) ;


    return 0 ;

}
