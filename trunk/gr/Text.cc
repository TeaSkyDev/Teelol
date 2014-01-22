#include "Text.hh"
using namespace std;


Text::Text(int x, int y, int h, int l): m_x(x), m_y(y), m_h(h), m_l(l) {
  m_fond = SDL_CreateRGBSurface(SDL_HWSURFACE, l, h, 32,0,0,0,0);
  SDL_FillRect(m_fond, NULL, SDL_MapRGB(m_fond->format, 255,255,255));
  TTF_Font * f = TTF_OpenFont("../const/Font.ttf",10);
  SDL_Color col = {0,0,0}; 
      
  m_content = TTF_RenderText_Blended(f, "", col);
  
}




string Text::getText(){
  return m_text;
}


void Text::pass_row(){
  while(SDL_PollEvent(&e)){
    for(int i = 'a' ; i < 'z'+1 ; i++){
      cout<<i<<endl;
      if(e.key.keysym.sym == i){
	m_text += i;
	e.key.keysym.sym = (SDLKey)0;
	int deb = m_text.length() - 10;
      TTF_Font * f = TTF_OpenFont("../const/Font.ttf",20);
      SDL_Color col = {0,0,0}; 
      if(deb < 0) deb = 0;
      string t = m_text.substr(deb, m_text.length()-1);
      m_content = TTF_RenderText_Blended(f, t.c_str(), col);
      TTF_CloseFont(f);
      }
    }
    SDL_Delay(10);
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
