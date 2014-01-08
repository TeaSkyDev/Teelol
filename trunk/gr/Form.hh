#ifndef _Form
#define _Form



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <iostream> 
#include "Ecran.hh"
#include <boost/lexical_cast.hpp>
#include <math.h>

#include "Const.hh"

using namespace std;


//vitesse de deplacement des objets
struct speed_t{
  int m_x;
  int m_y;
};

struct point{
    int x, y;
};

//représente le type de forme (décor, character, bullet)
enum type_t {
  FORM, CHARACTER, BULLET, ROTABLE, ITEM
};


class Form{
  public :
  Form(int x, int y, int h, int l);
  //prend en entree un chemin vers une image
  virtual void set_image(Image_t img);


  int get_l();
  int get_h();
  int get_x();
  int get_y();
  Image_t get_img();
  virtual type_t get_type();
  virtual void loose_life(int);
  int x_to_sig();
  int y_to_sig();
  int h_to_sig();
  int l_to_sig();
  void set_x(int x);
  void set_y(int y);
  speed_t get_speed();
  bool get_wrong_img(){return m_wrong_img;}
  void set_screen(Ecran * e);
  virtual void show();
  ~Form();
  
protected:
  Image_t m_img;
  bool m_wrong_img;
  SDL_Surface * m_surf;
  int m_x;
  int m_y;
  int m_h; 
  int m_l;
  Ecran * m_e;
  speed_t m_speed;
  Const c;
};



#endif
