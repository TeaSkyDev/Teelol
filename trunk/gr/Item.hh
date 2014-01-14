#ifndef _ITEM
#define _ITEM


enum ITEM_T{
  AMMO , LIFE
};

#include "Character.hh"
#include "Collision.hh"
class Item : public Form
{

public:

  Item(int x, int y, int h, int l, ITEM_T type);
  type_t get_type();
  ITEM_T get_item_type();
  void add_obstacle(Form &f);
  void pass_row();
  collision_t collide();
  void show();
  void hide();
  void unhide();
  bool hidden();

private:
  ITEM_T m_type;
  vector <Form*> m_obstacle;
  int m_wait;

};


#endif
