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

private:
  int m_dmg;
  vector<Form *> m_obstacle;
};




#endif
