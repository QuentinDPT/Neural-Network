#ifndef SDL_WIN_HPP
#define SDL_WIN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class SDL_Win : SDL_Interface
{
    public:
        SDL_Win(char *name, unsigned int width, unsigned int height, Color bgColor);
        SDL_Win(char *name, unsigned int width, unsigned int height, Color bgColor);
        virtual ~SDL_Win();

    protected:

    private:
        std::string  m_name ;
        unsigned int m_width ;
        unsigned int m_height ;
        Color        m_bgColor ;
};

#endif // SDL_WIN_HPP
