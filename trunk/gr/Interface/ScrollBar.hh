#ifndef _SCROLLBAR
#define _SCROLLBAR

#include <SDL/SDL.h>
#include "../Ecran.hh"
#include "../Event.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;
#define signals /**/


class ScrollBar {
public:
    
    ScrollBar(int, int, int, int);
    void pass_row(Event&);
    void grown(int);
    void show(Ecran *);
		      
public signals:
		   
    
    signal<void(int)> scroll; //signal avec le pourcentage de la barre


private:
    SDL_Surface * m_contour, *m_bar;
    int anc_x, anc_y;
    int m_lines;
    int m_x, m_y, m_h, m_l;
    int m_yb, m_hb;
    bool m_click;
    int m_lines_size;
    double m_purcent;

    bool is_inside(int, int);

};

#endif
