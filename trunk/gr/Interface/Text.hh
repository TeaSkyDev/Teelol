#ifndef _TEXT
#define _TEXT


#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "../Ecran.hh"
#include "../Event.hh"
#include <iostream>
#include <boost/signals2.hpp>

using boost::signals2::signal;


class Text{
public:
    Text(int, int, int h,int l, int id);
    std::string getText();
    void pass_row(Event);
    void show(Ecran *);
    bool Validated();
    void set_focus(bool);
    int getId();

    //slot


    //signal doivent être public
    
    signal<void(int)> focused;
    signal<void(string)> value_change;
    signal<void(string)> validated;


private:
    bool is_inside(int, int);
    bool verif_type(Uint16);
    int m_id;
    SDL_Event e;
    SDL_Surface * m_fond;
    SDL_Surface * m_content;
    TTF_Font * m_f;
    SDL_Color m_col;
    std::string m_text;
    int m_h, m_l, m_x, m_y;
    int m_delai;
    int m_anc_key;
    bool m_validated, m_focus;
};




#endif 
