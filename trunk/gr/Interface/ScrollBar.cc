#include "ScrollBar.hh"

ScrollBar::ScrollBar(int x, int y, int h, int l) :m_x(x), m_y(y), m_h(h), m_l(l) {
    m_lines = 10;
    m_yb = m_y + 1;
    m_hb = m_h-2;
    m_contour = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_h, 32, 0,0,0,0);
    m_bar = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_hb, 32, 0,0,0,0);
    SDL_FillRect(m_contour, NULL, SDL_MapRGB(m_contour->format,255,255,255));
}


void ScrollBar::add_lines(int nb){
    m_lines = nb;
    if(m_lines > 10) {
	m_hb = m_h - (m_lines + 10);
    }
}

void ScrollBar::pass_row(Event e) {
    if(!m_click) {
	if(is_inside(e().m_x, e().m_y) && e[LEFT_CL]) {
	    m_click = true;
	    anc_y = e().m_y;
	}
    }
    else {
	if(!e[LEFT_CL]) {
	    m_click = false;
	}
	else {
	    if(e().m_y > m_y + m_h) {
		m_yb = m_y + m_h - m_hb;
	    } else if(e().m_y < m_y ) {
		m_yb = m_y + 1;
	    } else if (anc_y < e().m_y) {
		m_yb += e().m_y - anc_y;
		anc_y = e().m_y;
		if(m_yb + m_hb > m_y + m_h) {
		    m_yb = m_y + m_h - m_hb;
		}
	    } else if (anc_y > e().m_y) {
		m_yb += e().m_y - anc_y;
		anc_y = e().m_y;
		if(m_yb < m_y) {
		    m_yb = m_y;
		}
	    }
		   
	}
	
    }
}


void ScrollBar::show(Ecran * e){
    m_bar = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_hb, 32, 0,0,0,0);
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    e->put(m_contour, rect);
    rect.y = m_yb;
    e->put(m_bar, rect);
}


bool ScrollBar::is_inside(int x, int y) {
    if(x >= m_x && x <= m_x + m_l && y >= m_yb && y <= m_yb + m_hb) {
	return true;
    }
    else {
	return false;
    }
}
