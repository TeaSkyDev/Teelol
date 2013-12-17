#ifndef _BULLET
#define _BULLET

#include "Form.hh"

class Bullet: public Form{
public:
  Bullet(int x, int y, int h, int l, int dmg, string img);
  int get_dmg();

  

private:
  int m_dmg;

};




#endif
