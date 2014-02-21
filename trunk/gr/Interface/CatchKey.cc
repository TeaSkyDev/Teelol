#include "CatchKey.hh"
using namespace std;


CatchKey::CatchKey(int x, int y, int h, int l) : Focusable(), m_x(x), m_y(y), m_h(h), m_l(l){
    m_fond = SDL_CreateRGBSurface(SDL_HWSURFACE, l,h, 32,0,0,0,0);
    SDL_FillRect(m_fond, NULL, SDL_MapRGB(m_fond->format, 255,200,255));
    TTF_Init();
    m_font = TTF_OpenFont("../const/Font.ttf", 15);
    m_color = {0,0,0};
    m_content = TTF_RenderText_Blended(m_font, "", m_color);
    m_focus = false;
    m_key = SDLK_EURO;
}




string CatchKey::getText() {
    return m_text;
}



void CatchKey::translate() {
    switch ( m_key ) {
    case SDLK_UP: m_text = "UP"; break;
    case SDLK_DOWN: m_text = "DOWN"; break;
    case SDLK_LEFT: m_text = "LEFT"; break;
    case SDLK_RIGHT: m_text = "RIGHT"; break;
    default: m_text = m_key; break;
    }
    if ( m_key >= SDLK_KP0 && m_key <= SDLK_KP9 ) {
	m_text = m_key - SDLK_KP0;
    }
}


void CatchKey::pass_row(Event & e) {
    if ( m_focus ) {
	if ( e.getEvent().type == SDL_KEYDOWN ) {
	    m_key = e.getEvent().key.keysym.sym;
	    translate();
	    m_content = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);
	    m_focus = false;
	    value_change(m_text);
	}
    } else {
	if ( is_inside(e().m_x, e().m_y) && e[LEFT_CL] ) {
	    m_text = "???";
	    m_content = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);
	    m_focus = true;
	    focused(m_id);
	}
    }
}



bool CatchKey::is_inside(int x, int y) {
    if ( m_x >= m_x && x <= m_x + m_l && y >= m_y && y <= m_y + m_h ) {
	return true;
    } else {
	return false;
    }
}



void CatchKey::set_focus(bool f) {
    m_focus = f;
    if ( f ) {
	focused(m_id);
    }
}


SDLKey CatchKey::getKey() {
    return m_key;
}



void CatchKey::show( Ecran * e ) {
    if ( m_focus ) {
	SDL_Surface * doublefond = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l + 4, m_h + 4, 32 , 0,0,0,0);
	SDL_FillRect(doublefond, NULL, SDL_MapRGB(doublefond->format, 255,20,255));
	SDL_Rect r;
	r.x = m_x - 2; r.y = m_y - 2;
	e->put(doublefond, r);
    }
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    e->put(m_fond, rect);
    if ( m_content ) {
	rect.x += m_l/2 - m_content->w/2;
	rect.y += m_h/2 - m_content->h/2;
	e->put(m_content, rect);
    }
}
