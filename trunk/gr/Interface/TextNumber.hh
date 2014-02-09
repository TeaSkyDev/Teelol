#ifndef _TEXTNUMBER
#define _TEXTNUMBER


#include "../Event.hh"
#include "../Ecran.hh"
#include "Focusable.hh"
#include <iostream>
#include <sstream>

#define signals /**/

class TextNumber : public Focusable{
public:

    TextNumber(int, int, int, int);
    std::string getValue();
    int getValue_int();
    void pass_row(Event & e);
    void show(Ecran * sc);

			 
public signals:

    signal<void(int)> value_change;

private:
    
    bool is_inside(int, int);
    bool verif_type(Uint16);
    SDL_Surface * m_fond, *m_content;
    TTF_Font * m_font;
    SDL_Color m_col;
    std::stringstream m_flux;
    std::string m_value;
    int m_h, m_l, m_x, m_y;
    int m_delai;
    int m_anc_key;


};


#endif
