#ifndef _Ecran
#define _Ecran

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Const.hh"
#include <iostream>
using namespace std;


  class Ecran{
    
  public:
    Ecran(int hauteur, int largeur);
    void Resize(int hauteur, int largeur);
    void pause();
    void Flip();
    void put(SDL_Surface * s, SDL_Rect r); 
    void clean();
    int get_h();
    int get_l();
    ~Ecran();
  private:
  
    SDL_Surface * ecran, *m_fond;
    
    int height, width;
    Const c;
  };

#endif
