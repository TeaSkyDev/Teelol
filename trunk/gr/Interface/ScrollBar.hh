#ifndef _SCROLLBAR
#define _SCROLLBAR

#include <SDL/SDL.h>
#include "../Ecran.hh"
#include "../Event.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;

class ScrollBar {
public:
    
    ScrollBar(int, int, int, int);
    void pass_row(Event);
    void add_lines(int);
    void show(Ecran *);
    //signal
    
    signal<void()> scroll_bottom;
    signal<void()> scoll_up;
    bool is_inside(int, int);

private:
    SDL_Surface * m_contour, *m_bar;
    int anc_x, anc_y;
    int m_lines;
    int m_x, m_y, m_h, m_l;
    int m_yb, m_hb;
    bool m_click;
};

#endif
