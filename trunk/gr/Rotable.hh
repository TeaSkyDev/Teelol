#ifndef _ROTABLE
#define _ROTABLE

#include "Form.hh"


class Rotable:public Form{
public:
  
  Rotable(int x, int y, int h, int l): Form(x,y,h,l){m_angle = 0;}
  void set_image(Image_t img);
  int get_xb();
  int get_yb();
  int get_xba();
  int get_yba();
  double get_angle();
  void set_angle(double angle);
  void rotate(double angle, int x, int y, int dist);
  void rotate_invacuo(double angle);




private:

  
  //les fnction suivantes doivent être appelé dans l'ordre
  void get_A();
  void get_B();
  void get_F();
  void get_D();
  void get_E();
  void get_C();

  SDL_Surface *m_sauv, *m_sauv2;
  int m_angle;
  point A, B, C, D, E, F, O;


  /*
          CBx-----------xD
            |           |
    Ox-----Ax           |
            |           |
	   Fx-----------xE
   */

  int m_dist;
  

};




#endif
