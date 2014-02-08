#include "ListItem.hh"
using namespace std;

ListItem::ListItem(string text) {
    TTF_Init();
    m_text = text;
    m_police = TTF_OpenFont("../const/Font.ttf", 20);
    m_color = {0,0,0};
}


void ListItem::pass_row(Event &e) {
    if(e[LEFT_CL] && is_inside(e().m_x, e().m_y)) {
	if(m_clicked && !m_double_clicked) {
	    m_double_clicked = true;
	    double_clicked();
	} else {
	    m_delay = 0;
	    m_clicked = true;
	    clicked(m_id);
	}
    } else {
	if( m_delay < 10 && m_delay != -1) {
	    m_delay ++;
	} else {
	    m_delay = -1;
	    m_clicked = false;
	}
    }
}


bool ListItem::is_inside(int x, int y) {
    if( x >= m_x && x <= m_x + m_l && y >= m_y && y <= m_y + m_h ) {
	return true;
    } else {
	return false;
    }
}

int & ListItem::id() {
    return m_id;
}


int & ListItem::x() {
    return m_x;
}



int & ListItem::y() {
    return m_y;
}

int & ListItem::h() {
    return m_h;
}

int & ListItem::l() {
    return m_l;
}

void ListItem::set_y(int y) {
    m_sauve_y = y;
}

int ListItem::sauve_y() {
    return m_sauve_y;
}


string ListItem::text() {
    return m_text;
}


SDL_Color & ListItem::color() {
    return m_color;
}


TTF_Font * ListItem::police() {
    return m_police;
}
