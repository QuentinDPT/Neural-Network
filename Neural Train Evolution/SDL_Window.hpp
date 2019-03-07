#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>
#include <thread>

typedef struct{
    unsigned char r,g,b,a ;
} COLOR ;

typedef struct{
    int x, y ;
}POSITION ;

typedef struct{
    bool exitOnClose ;
    bool refreshManual ;
    unsigned int  refreshWithoutFocus ;
    unsigned int  refreshWithoutMouseTrack ;
    unsigned int  refresh ;
} RULES ;

class SDL_Window
{
    public:
        SDL_Window(std::string name, unsigned int length, unsigned int height, COLOR bgColor);
        SDL_Window(char* name, unsigned int length, unsigned int height, COLOR bgColor) ;
        virtual ~SDL_Window();

        void exit() ;

        void hide() ;
        void show() ;

        POSITION getPosition() ;
        void*    getSize() ;


    protected:
        virtual void refresh() ;
        virtual void draw() ;

        RULES         m_rules ;

        SDL_Window   *m_window ;
        SDL_Renderer *m_renderer ;
        SDL_Event    *m_eventHandler ;

    private:
        void _refreshEvents() ;
        unsigned int  m_wantedRefreshTime ;

        void _threadRefresher(SDL_Window *win) ;
        bool          m_stopThread ;
        std::thread   m_refreshThread ;

        std::string   m_name ;
        unsigned int  m_length ;
        unsigned int  m_height ;
        COLOR         m_bgColor ;
        POSITION      m_position ;

        std::vector<SDL_Window*> m_childs ;
};

#endif // SDL_WINDOW_HPP
