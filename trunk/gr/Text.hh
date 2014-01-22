#ifndef _TEXT
#define _TEXT


#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "Ecran.hh"
#include "Event.hh"
#include <iostream>

class Text{
public:
  Text(int, int, int h,int l);
  std::string getText();
  void pass_row(SDL_Event *);
  void show(Ecran *);
  bool Validated();

private:

  bool verif_type(Uint16);
  
  SDL_Event e;
  SDL_Surface * m_fond;
  SDL_Surface * m_content;
  TTF_Font * m_f;
  SDL_Color m_col;
  std::string m_text;
  int m_h, m_l, m_x, m_y;
  int m_delai;
  int m_anc_key;
  bool m_validated;
};




#endif 
