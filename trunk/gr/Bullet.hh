#ifndef _BULLET
#define _BULLET

#include "Form.hh"
#include "Collision.hh"
#include <vector>
#include <math.h>

class Bullet: public Form{
public:
  Bullet(int x, int y, int h, int l, int dmg, string img);
  int get_dmg();
  void pass_row();
  void explode();
  void add_obstacle(Form * f);
  direction_t collide();
  void set_speed(int angle); //calcule la vitesse a laquelle va devoir aller la balle

private:
  int m_dmg;
  vector<Form *> m_obstacle;
};




#endif
