#include "SDL_Interface.hpp"

SDL_Interface::SDL_Interface(Color bgColor) :
    m_bgColor(bgColor)
{
    //ctor
}

SDL_Interface::~SDL_Interface()
{
    //dtor
}

void SDL_Interface::refresh(){
    for(unsigned int i = 0 ; i < m_sceneLayers.size() ; i++)
        m_sceneLayers[i](m_render) ;
}
