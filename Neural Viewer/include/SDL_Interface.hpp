#ifndef SDL_INTERFACE_HPP
#define SDL_INTERFACE_HPP

struct Color{
    unsigned char r, g, b, a ;
};

class SDL_Interface
{
    public:
        SDL_Interface(Color bgColor);
        virtual ~SDL_Interface();

        void refresh() ;

    protected:

    private:
        Color m_bgColor ;
};

#endif // SDL_INTERFACE_HPP
