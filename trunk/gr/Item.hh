#ifndef _ITEM
#define _ITEM


enum ITEM_T{
  AMMO , LIFE
};

#include "Form.hh"
#include "Collision.hh"
class Item : public Form
{

public:

  Item(int x, int y, int h, int l, ITEM_T type);
  ITEM_T get_type();
  void pass_row();
  collision_t collide();


private:
  ITEM_t m_type;
  vector <Form*> m_obstacle;
  

};


#endif
