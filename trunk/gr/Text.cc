#include "Text.hh"
using namespace std;


Text::Text(int x, int y, int h, int l): m_x(x), m_y(y), m_h(h), m_l(l) {
  m_fond = SDL_CreateRGBSurface(SDL_HWSURFACE, l, h, 32,0,0,0,0);
  SDL_FillRect(m_fond, NULL, SDL_MapRGB(m_fond->format, 255,255,255));
  m_f = TTF_OpenFont("../const/Font.ttf",20);
  m_col = {0,0,0};       
  m_content = TTF_RenderText_Blended(m_f, "", m_col);
  m_validated = false;
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

void Text::pass_row(SDL_Event * e){
  if(e->type == SDL_KEYDOWN){
    if(m_text.length() <= 20){
      if(verif_type(e->key.keysym.sym)){
	if(m_anc_key != e->key.keysym.sym || m_delai >= 20)
	  m_text += e->key.keysym.sym;
      }
    }
    if(e->key.keysym.sym == SDLK_BACKSPACE){
      m_text = m_text.substr(0, m_text.length()-1);
    }
    if(e->key.keysym.sym == SDLK_RETURN && m_text.length() != 0){
      m_validated = true;
    }
    int deb = m_text.length() - 10;
    if(deb < 0) deb = 0;
    string t = m_text.substr(deb, m_text.length());
    m_content = TTF_RenderText_Blended(m_f, t.c_str(), m_col);
    if(m_anc_key != e->key.keysym.sym){
      m_anc_key = e->key.keysym.sym;
      m_delai = 0;
    }
    m_delai++;
  }
  if(e->type == SDL_KEYUP){
    m_anc_key = 0;
    m_delai = 0;
  }
}


void Text::show(Ecran * e){
  SDL_Rect rect;
  rect.x = m_x;
  rect.y = m_y;
  e->put(m_fond, rect);
  rect.x += 2;
  rect.y += 2;
  e->put(m_content, rect);

}
