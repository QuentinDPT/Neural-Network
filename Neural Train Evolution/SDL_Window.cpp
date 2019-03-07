#include "SDL_Window.hpp"

#include <time.h>

SDL_Window::SDL_Window(std::string name, unsigned int length, unsigned int height, COLOR bgColor)
{
    SDL_Window(name.c_str(), length, height, bgColor) ;
}

SDL_Window::SDL_Window(char* name, unsigned int length, unsigned int height, COLOR bgColor)
{
    m_stopThread = false ;
    m_wantedRefreshTime = 30 ;
    m_refreshThread = std::thread(_threadRefresher, this, this) ;


    // Ouverture de le SDL et de ses extensions.
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        //fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        //return 0;
        return ;
    }
    /*
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return 0;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
      fprintf(stderr,"Erreur d'open audio %s", Mix_GetError());
      return 0;
    }
    Mix_AllocateChannels(NB_MAX_SON);
    */

    //initialisation_son();
    /*
    Mix_Chunk* son[NB_MAX_SON];
    for(int i=0;i<NB_MAX_SON;i++)
    {
        son[i]=NULL;
    }
    */

    m_window = SDL_CreateWindow("test",
                                SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                750, 500 ,
                                SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_SOFTWARE);

    SDL_SetRenderDrawColor(m_renderer,
                           m_bgColor.r,m_bgColor.g,m_bgColor.b,255);

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

#include <iostream>
SDL_Window::~SDL_Window()
{
    //dtor
    m_stopThread = true ;
    m_refreshThread.join() ;
}


void SDL_Window::refresh(){

}

void SDL_Window::draw(){

}

void SDL_Window::_refreshEvents(){
    int *resultat ;
    *resultat=0;
    if(SDL_PollEvent(m_eventHandler))
    {
        switch(m_eventHandler->type)
        {
        case(SDL_MOUSEBUTTONDOWN):
            if(m_eventHandler->button.button==SDL_BUTTON_RIGHT)
                *resultat=8;
            else if(m_eventHandler->button.button==SDL_BUTTON_LEFT)
                *resultat=7;
            else *resultat=0;
            return ;
        case(SDL_MOUSEBUTTONUP):
            if(m_eventHandler->button.button==SDL_BUTTON_RIGHT)
                *resultat=6;
            else if(m_eventHandler->button.button==SDL_BUTTON_LEFT)
                *resultat=5;
            else *resultat= 0;
            return ;
        case(SDL_KEYDOWN):
            *resultat= 4;
            return ;
        case(SDL_KEYUP):
            *resultat= 3;
            return ;
        case(SDL_MOUSEMOTION):
            *resultat= 2;
            return ;
        case(SDL_QUIT):
            *resultat= 1;
            return ;
        default:
            return ;
        }
    }
}


void SDL_Window::_threadRefresher(SDL_Window *win){
    unsigned int timer = clock();

    while(!win->m_stopThread){
        win->_refreshEvents() ;
        win->refresh() ;
        win->draw() ;

        while(clock() - timer < win->m_wantedRefreshTime) ;
        timer = clock() ;
    }
}
