#ifndef _LISTITEM
#define _LISTITEM

#include "../Event.hh"
#include <boost/signals2.hpp>
#include <SDL/SDL_ttf.h>
#include <iostream>

using boost::signals2::signal;


#define signals /**/

class ListItem {

public:

    ListItem(std::string text);
    void pass_row(Event &e);
    int & id();
    int & x();
    int &y();
    int &h();
    int &l();
    SDL_Color & color();
    TTF_Font *police();
    void set_y(int);
    int sauve_y();
    std::string text();

private:
    bool is_inside(int, int);
    TTF_Font * m_police;
    SDL_Color m_color;
    
    int m_id;
    std::string m_text;
    bool m_clicked, m_double_clicked;
    int m_delay;
    int m_sauve_y;
    int m_x, m_y, m_h, m_l;
			  
public signals:

    signal<void(int)> clicked;
    signal<void()> double_clicked;


};



#endif
