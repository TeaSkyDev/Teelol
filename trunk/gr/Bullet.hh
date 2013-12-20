#ifndef _BULLET
#define _BULLET

#include "Form.hh"
#include "Collision.hh"
#include <vector>
#include <math.h>

class Bullet: public Form{
public:
  Bullet(int x, int y, int h, int l, int dmg, double angle, string img);
  int get_dmg();
  void pass_row();
  void explode();
  void add_obstacle(Form * f);
  direction_t collide();
  void set_speed(int temps); //calcule la vitesse a laquelle va devoir aller la balle

private:
  int m_dmg;
  double m_angle;
  int m_speed_init;
  int m_temps;
  vector<Form *> m_obstacle;

  /* tmp */
  double m_vx;
  double m_vy;
  int m_x_init;
  int m_y_init;
};




#endif
