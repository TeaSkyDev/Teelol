#include "Item.hh"


Item::Item(int x, int y, int h, int l, ITEM_T type):Form(x,y,h,l){
  m_type = type;
  switch(m_type){
  case AMMO:
    set_image(I_GRENADE);break;
  case LIFE:
    set_image(I_COEUR); break;
  }
}


ITEM_T Item::get_type(){
  return m_type;
}

void pass_row(){
  collision_t col = collide();
  if(m_wait == 0){
    if(col.dir.col_y != NONE || col.dir.col_x != NONE){
      if(col.type == CHARACTER){
	switch(m_type){
	case AMMO:
	  col.element->get_ammo()->pick_up(5);break;
	case LIFE:
	  col.element->take_life(5);break;
	}
	m_wait = 150;
      }
    }
  }
  else m_wait --;
}

void Item::show(){
  if(m_wait == 0){
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.h = m_h;
    rect.w = m_l;
    m_e->put(m_surf,rect);
  }
}

collision_t Item::collide(){
  Collision col(this, m_obstacle);
  return c.get_collision();
}
