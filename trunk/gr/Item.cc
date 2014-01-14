#include "Item.hh"


Item::Item(int x, int y, int h, int l, ITEM_T type):Form(x,y,h,l){
  m_type = type;
  switch(m_type){
  case AMMO:
    set_image(I_GRENADE);break;
  case LIFE:
    set_image(I_COEUR); break;
  }
  m_wait = 0;
  m_speed.m_x = 0;
  m_speed.m_y = 0;
  m_just_showed = false;
}


type_t Item::get_type(){
  return ITEM;
}

ITEM_T Item::get_item_type(){
  return m_type;
}

void Item::add_obstacle(Form &f) {
  m_obstacle.push_back(&f);
}

void Item::pass_row(){
  collision_t col = collide();
  if(m_wait == 0){
    if(col.type == CHARACTER){
      cout << "test" << endl;
      Character * c = (Character*)col.element;
      switch(m_type){
      case AMMO:	  
	//if(c->get_ammo()->get_NbAmmo() != c->get_ammo()->get_max()) {
	  c->get_ammo()->pick_up(5);
	  this->hide();
	  //}
	break;
      case LIFE:
	//	if(c->get_life() != 10) {
	  c->take_life(5);
	  this->hide();
	  //}
	break;
      }
      m_wait = 150;
    }
    
  }
  else {
    m_wait --;
    if(m_wait == 0) {
      m_just_showed = true;
    }
  }
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

void Item::unhide(){
  m_wait = 0;
}

void Item::hide(){
  m_wait = 1;
}

bool Item::hidden(){
  return m_wait >= 1;
}
collision_t Item::collide(){
  Collision col(this, m_obstacle);
  return col.get_collision();
}

bool Item::get_just_showed() {
  if(m_just_showed) {
    m_just_showed = false;
    return true;
  }
  return false;
}
