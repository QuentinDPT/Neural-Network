#define SDL_MAIN_HANDLED


#include <iostream>         // cout, cin, cerr, ...
#include <windows.h>        // getch(), Sleep(), ...

#include "SDL_Win.hpp"      // SDL_Win(), Color(), SDL_Interface(), ...


using namespace std ;

void fristLayer(SDL_Renderer *render){
    cout << "affichage couche par couche\n" ;

    SDL_Rect rectangle={0,0,100,560};
    SDL_SetRenderDrawColor(render,255,0,0,255);
    SDL_RenderDrawRect(render,&rectangle);
    SDL_SetRenderDrawColor(render,0,0,0,255);  // On retourne à la couleur par défaut
}

int main()
{

    SDL_Win win("Neural Viewer [Beta]",         // nom
                1400,850,                       // taille
                Color::fromHex(0x000000FF)) ;   // couleur




    win.show() ;

    win.sleep(1000) ;

    SDL_Interface itr(Color::fromHex(0xFF00FFFF)) ;
    itr.addDrawLayer(&fristLayer) ;
    win.applyInterface(itr) ;

    for(unsigned int i = 0 ; i < 10000 ; i++)
        win.refresh() ;

    win.sleep(1000) ;


    return 0 ;

}
