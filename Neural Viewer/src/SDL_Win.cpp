#include "SDL_Win.hpp"

#include <iostream>         // cerr, cout, cin
SDL_Win::SDL_Win(char *name, unsigned int width, unsigned int height, Color bgColor) :
    m_name(name),
    m_width(width), m_height(height),
    m_itr(bgColor)
{
    // Ouverture de le SDL et de ses extensions.
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        std::cerr << "Échec de l'initialisation de la SDL " << SDL_GetError() << '\n' ;
        return ;
    }

    if(TTF_Init() == -1)
    {
        std::cerr << "Erreur d'initialisation de TTF_Init " << SDL_GetError() << '\n' ;
        return ;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        std::cerr << "Erreur d'open audio " << Mix_GetError() << '\n' ;
        return ;
    }

    Mix_AllocateChannels(NB_MAX_SON);

    /// INITIALISATION DES SONS
    //initialisation_son();
    // Initialisation de la fenetre
    m_win=SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height ,SDL_WINDOW_SHOWN);
    m_render=SDL_CreateRenderer(m_win,-1,SDL_RENDERER_SOFTWARE);

    // Affichage d'un arrière plan
    SDL_SetRenderDrawColor(m_render,
                           m_itr.getBgColor().r, m_itr.getBgColor().g, m_itr.getBgColor().b, 255);
    SDL_RenderClear(m_render) ;
    SDL_RenderPresent(m_render) ;
}

SDL_Win::~SDL_Win()
{
    //dtor
}

bool SDL_Win::show(){


    return true ;
}

bool SDL_Win::applyInterface(const SDL_Interface &itr){
    m_itr = itr ;

    return true ;
}

void SDL_Win::refresh() {
    SDL_SetRenderDrawColor(m_render,
                           m_itr.getBgColor().r, m_itr.getBgColor().g, m_itr.getBgColor().b, 255);

    SDL_RenderClear(m_render) ;

    m_itr.refresh() ;

    SDL_RenderPresent(m_render) ;
}
