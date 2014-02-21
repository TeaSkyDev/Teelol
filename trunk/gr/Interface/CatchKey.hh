#ifndef _CATCH
#define _CATCH


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Focusable.hh"
#include "../Event.hh"
#include "../Ecran.hh"
#include <iostream>
#include <boost/signals2.hpp>
using boost::signals2::signal;

class CatchKey : public Focusable {
    
public:
    
    CatchKey(int, int, int, int);
    std::string getText();
    SDLKey getKey();
    void pass_row(Event&);
    void show(Ecran *);
    void set_focus(bool);



    signal<void(string)> value_change;




private:
    bool is_inside(int, int);
    void translate();
    SDL_Surface * m_fond;
    SDL_Surface * m_content;
    TTF_Font * m_font;
    SDL_Color m_color;
    std::string m_text;
    int m_h, m_l, m_x, m_y;
    SDLKey m_key;
};
		






#endif
