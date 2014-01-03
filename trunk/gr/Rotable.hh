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
  void rotate_to(double angle, int x, int y, int dist);
  void zoom(double);
  void recalibrate();

private:

  SDL_Surface *m_sauv, *m_sauv2;
  int m_angle;
};




#endif
