#include "TextNumber.hh"

TextNumber::TextNumber(int x, int y, int h, int l, int nb):m_x(x), m_y(y), m_h(h), m_l(l) {
    TTF_Init();
    m_fond = SDL_CreateRGBSurface(SDL_HWSURFACE, l, h, 32, 0,0,0,0);
    SDL_FillRect(m_fond, NULL, SDL_MapRGB(m_fond->format, 255,255,255));
    m_font = TTF_OpenFont("../const/Font.ttf",20);
    m_col = {0,0,0};
    m_content = TTF_RenderText_Blended(m_font, " ", m_col);
    m_focus = false;
    m_nb = nb;
}


string TextNumber::getValue() {
    return m_value;
}

int TextNumber::getValue_int() {
    if( m_value.length() > 0 ) {
	stringstream ss(m_value);
	int s;
	ss >> s;
	return s;
    } else {
	return 0;
    }
}

void TextNumber::set_value(int value) {
    m_set = true;
    stringstream ss;
    ss << value;
    m_value = ss.str();
    m_content = TTF_RenderText_Blended(m_font, m_value.c_str(), m_col);
}

bool TextNumber::verif_type(Uint16 e) {
    if(e >= SDLK_KP0 && e <= SDLK_KP9) {
	return true;
    }
    return false;
}


bool TextNumber::is_inside(int x , int y) {
    if( x >= m_x && x <= m_x + m_l && y >= m_y && y <= m_y + m_h ) {
	return true;
    } else {
	return false;
    }
}

void TextNumber::pass_row(Event & e) {
    if( m_focus ) {
	if( e.getEvent().type == SDL_KEYDOWN ) {
	    if( m_nb > m_value.length() ) {
		if( verif_type( e.getEvent().key.keysym.sym ) ) {
		    if( m_anc_key != e.getEvent().key.keysym.sym || m_delai >= 20 ) {
			if ( m_set ) {
			    m_value = "";
			    m_set = false;
			}	
			m_value += (char)(e.getEvent().key.keysym.sym - 208);
			stringstream ss(m_value);
			int s;
			ss >> s;
			value_change(s);
		    }
		}
	    }
	    if(e.getEvent().key.keysym.sym == SDLK_BACKSPACE ) {
		m_value = m_value.substr(0, m_value.length() - 1);
	    }
	    
	    if( e.getEvent().key.keysym.sym == SDLK_RETURN ) {
		m_set = true;
		validated();
	    }
	    
	    int deb = m_value.length() - 10;
	    if ( deb < 0 ) {
		deb = 0;
	    }
	    string t = m_value;
	    t.substr(deb, m_value.length());
	    m_content = TTF_RenderText_Blended(m_font, t.c_str(), m_col);
	    if( m_anc_key != e.getEvent().key.keysym.sym ) {
		m_anc_key = e.getEvent().key.keysym.sym;
		m_delai = 0;
	    }
	    m_delai++;
	
	}
	if( e.getEvent().type == SDL_KEYUP ) {
	    m_delai = 0;
	    m_anc_key = 0;
	}	
    }
}


void TextNumber::show(Ecran * e) {
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    e->put(m_fond, rect);
    if(m_content) {
	rect.x = rect.x + m_fond->w/2 - m_content->w/2;
	rect.y = rect.y + m_fond->h/2 - m_content->h/2;
	e->put(m_content, rect);
    }
}


int &TextNumber::x() {
    return m_x;
}

int &TextNumber::y() {
    return m_y;
}

int &TextNumber::h() {
    return m_h;
}

int &TextNumber::l() {
    return m_l;
}
