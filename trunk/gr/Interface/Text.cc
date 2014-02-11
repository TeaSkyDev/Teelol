#include "Text.hh"
using namespace std;



Text::Text(int x, int y, int h, int l): m_x(x), m_y(y), m_h(h), m_l(l){
  m_fond = SDL_CreateRGBSurface(SDL_HWSURFACE, l, h, 32,0,0,0,0);
  SDL_FillRect(m_fond, NULL, SDL_MapRGB(m_fond->format, 255,200,255));
  TTF_Init();
  m_f = TTF_OpenFont("../const/Font.ttf",15);
  m_nb_lettre = l/12;
  cout << m_nb_lettre << endl;
  m_col = {0,0,0};       
  m_content = TTF_RenderText_Blended(m_f, "", m_col);
  m_validated = false;
  m_focus = false;
  m_delai = 400;
  m_anc_key = 0;
}




string Text::getText(){
  return m_text;
}


bool Text::Validated(){
  return m_validated;
}

bool Text::verif_type(Uint16 e){

  if(e >= '0' && e <= '9')
    return true;
  if(e >= 'A' && e <= 'Z')
    return true;
  if(e >= 'a' && e <= 'z')
    return true;
  if(e == ' ')
    return true;
  return false;
}

bool Text::is_inside(int x, int y) {
    if(x >= m_x && x <= m_x + m_l && y >= m_y && y <= m_y + m_h) {
	return true;
    }
    else {
	return false;
    }
}


void Text::pass_row(Event &e){
    if(m_focus) {
	if(e.getEvent().type == SDL_KEYDOWN) {
	    if(verif_type(e.getEvent().key.keysym.sym)) {
		if(m_anc_key != e.getEvent().key.keysym.sym || m_delai >= 20){
		    m_text += e.getEvent().key.keysym.sym;
		    value_change(m_text);
		}
	    }
	    if(e.getEvent().key.keysym.sym == SDLK_BACKSPACE) {
		m_text = m_text.substr(0, m_text.length()-1);
		value_change(m_text);
	    }
	    if(e.getEvent().key.keysym.sym == SDLK_RETURN && m_text.length() != 0) {
		m_validated = true;
		validated(m_text);
	    }
	    
	    int deb = m_text.length() - m_nb_lettre;
	    if(deb < 0) {
		deb = 0;
	    }
	    string t = m_text.substr(deb, m_text.length()) + "|";
	    m_content = TTF_RenderText_Blended(m_f, t.c_str(), m_col);
	    if(m_anc_key != e.getEvent().key.keysym.sym){
		m_anc_key = e.getEvent().key.keysym.sym;
		m_delai = 0;
	    }
	    m_delai++;
	}
	if(e.getEvent().type == SDL_KEYUP){
	    m_anc_key = 0;
	    m_delai = 0;
	}
    }
    else {
	if(is_inside(e().m_x, e().m_y) && e[LEFT_CL]) {
	    m_focus = true;
	    focused(m_id);
	    int deb = m_text.length() - 10;
	    if(deb < 0) {
		deb = 0;
	    }
	    string t = m_text.substr(deb, m_text.length()) + "|";
	    m_content = TTF_RenderText_Blended(m_f, t.c_str(), m_col);
	}
    }
}


void Text::show(Ecran * e){
  SDL_Rect rect;
  rect.x = m_x;
  rect.y = m_y;
  e->put(m_fond, rect);
  if (m_content) {
      rect.x += m_l/2 - m_content->w/2;
      rect.y += m_h/2 - m_content->h/2;
      e->put(m_content, rect);
  }
}


void Text::set_focus(bool b){
    m_focus = b;
    cout<< m_id << " " << b << endl;
    if(b) {
	int deb = m_text.length() - m_nb_lettre;
	if(deb < 0) {
	    deb = 0;
	}
	string t = m_text.substr(deb, m_text.length()) + "|";
	m_content = TTF_RenderText_Blended(m_f, t.c_str(), m_col);	
	focused(m_id);
    }
    else {
	int deb = m_text.length() - m_nb_lettre;
	if(deb < 0) {
	    deb = 0;
	}
	string t = m_text.substr(deb, m_text.length());
	m_content = TTF_RenderText_Blended(m_f, t.c_str(), m_col);	
    }
}

