#ifndef _Form
#define _Form



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <iostream> 
#include "Ecran.hh"
#include <boost/lexical_cast.hpp>
#include <math.h>
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
    int get_xb();
    int get_yb();
    double get_angle();
    int x_to_sig();
    int y_to_sig();
    int h_to_sig();
    int l_to_sig();
    void set_x(int x);
    void set_y(int y);
    void set_angle(double angle);
    void rotate(double angle, int x, int y, int dist);
    void rotate_to(double angle, int x, int y, int dist);
    void recalibrate();
    speed_t get_speed();
    void set_screen(Ecran * e);
    void show();
    ~Form();

  protected:

    SDL_Surface * m_surf, *m_sauv, *m_sauv2;
    int m_x;
    int m_y;
    int m_h; 
    int m_l;
    int m_angle;
    Ecran * m_e;
    speed_t m_speed;
  };



#endif
