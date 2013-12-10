#ifndef _Form
#define _Form



#include <SDL/SDL.h>

#include <iostream> 
#include "Ecran.hh"
  using namespace std;


  //vitesse de deplacement des objets
  struct speed_t{
    int m_x;
    int m_y;
  };


  class Form{
  public :
    Form(int x, int y, int h, int l);
    //prend en entree un chemin vers une image
    void set_image(string img);
    int get_l();
    int get_h();
    int get_x();
    int get_y();
    speed_t get_speed();
    void show();
    ~Form();

  protected:

    SDL_Surface * m_surf;
    int m_x;
    int m_y;
    int m_h; 
    int m_l;
    Ecran * m_e;
    speed_t m_speed;
  };



#endif
