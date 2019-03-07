#include "SDL_Win.hpp"

SDL_Win::SDL_Win(char *name, unsigned int width, unsigned int height, Color bgColor) :
    SDL_Interface(bgColor),
    m_name(name),
    m_width(width), m_height(height)
{

}

SDL_Win::~SDL_Win()
{
    //dtor
}
