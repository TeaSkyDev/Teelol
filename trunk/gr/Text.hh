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
  void pass_row();
  void show(Ecran *);
  

private:
  
  SDL_Event e;
  SDL_Surface * m_fond;
  SDL_Surface * m_content;
  std::string m_text;
  int m_h, m_l, m_x, m_y;
};




#endif 
