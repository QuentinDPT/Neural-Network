#ifndef SDL_WIN_HPP
#define SDL_WIN_HPP

#define NB_MAX_SON 10


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "SDL_Interface.hpp"

struct SDL_EventRules {
    void *exit ;
    void *mouseMove ;
    void *mouseClick ;
    void *kbEvent ;

    SDL_EventRules() : exit(NULL), mouseMove(NULL), mouseClick(NULL), kbEvent(NULL) {} ;
} ;

class SDL_Win
{
    public:
        SDL_Win(char *name, unsigned int width, unsigned int height, Color bgColor) ;
        virtual ~SDL_Win() ;

        bool show() ;

        bool applyInterface(const SDL_Interface &itr) ;
        SDL_Interface getItr() const {
            return SDL_Interface(m_itr) ;
        } ;

        void sleep(unsigned int ms ) { SDL_Delay(ms) ; } ;

        void refresh() ;

    protected:

    private:
        std::string  m_name ;
        unsigned int m_width ;
        unsigned int m_height ;

        SDL_Interface m_itr ;

        SDL_Window   *m_win ;
        SDL_Renderer *m_render ;
};

#endif // SDL_WIN_HPP
