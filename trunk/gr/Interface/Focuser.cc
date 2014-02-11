#include "Focuser.hh"
using namespace std;

Focuser::Focuser() {
    m_select == -1;
    m_delay = 0;
}


void Focuser::operator()(int id) {
    for(auto it: m_focusable) {
	if(it->getId() != id) {
	    it->set_focus(false);
	}
    }
}


void Focuser::add_focusable(Focusable * t){
    m_focusable.push_back(t);
    t->set_focus(true);
    m_select == m_focusable.size() - 1;
    (*this)(t->getId());
}


void Focuser::pass_row(Event & e) {

    if ( e.getEvent().type == SDL_KEYDOWN ) {
	if ( m_delay > 4 ) {
	    if ( e.getEvent().key.keysym.sym == SDLK_TAB ) {
		if( m_select != -1 ) {
		    m_select++;
		    if ( m_select > m_focusable.size()-1 ) {
			m_select = 0;
		    }
		    m_focusable[m_select]->set_focus(true);
		    (*this)(m_focusable[m_select]->getId());
		}
		m_delay = 0;
	    }
	}
    } else if ( e.getEvent().type == SDL_KEYUP ) {
	m_delay = 5;
    }
	if ( m_delay != 11 ){
	    m_delay ++;
	}
}
