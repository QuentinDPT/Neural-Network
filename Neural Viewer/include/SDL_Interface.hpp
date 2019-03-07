#ifndef SDL_INTERFACE_HPP
#define SDL_INTERFACE_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>

struct Color{
    unsigned char r, g, b, a ;

    Color() : r(0), g(0), b(0), a(0) {} ;

    Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0 ){
        this->r = r ;
        this->g = g ;
        this->b = b ;

        this->a = a ;
    }

    Color(const Color &cpy){
        r = cpy.r ;
        g = cpy.g ;
        b = cpy.b ;
        a = cpy.a ;
    }

    static Color fromHex(unsigned int hex) {
        return Color( (hex & (0xFF<<24))>>24 ,
                      (hex & (0xFF<<16))>>16 ,
                      (hex & (0xFF<<8 ))>>8  ,
                       hex & (0xFF    )      ) ;
    } ;
};

class SDL_Interface
{
    public:
        SDL_Interface(Color bgColor);
        SDL_Interface(const SDL_Interface &cpy) ;
        virtual ~SDL_Interface();

        void refresh() ;
        void addDrawLayer(void(*fct)(SDL_Renderer*)){
            m_sceneLayers.push_back((void(*)(SDL_Renderer*))fct) ;
        } ;

        Color getBgColor() const { return Color(m_bgColor) ; } ;

        SDL_Renderer* getSDL_Renderer() const { return m_render ; } ;

    protected:
    private:
        Color m_bgColor ;

        SDL_Renderer *m_render ;

        std::vector<void(*)(SDL_Renderer*)> m_sceneLayers ;

};

#endif // SDL_INTERFACE_HPP
