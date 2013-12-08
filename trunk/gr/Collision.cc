#include "Collision.hh"

Collision::Collision(Form * f, vector <Form> tab){
  m_direction = NONE;
 for(int i = 0 ; i < tab.size() ; i++){
    direction_t t = is_inside(f, &tab[i]);
    if(t != NONE && m_direction != SOUTH)
      m_direction = t;
  }
}

Collision::Collision(Form * f, Form * t){
  //TODO
}

bool Collision::is_inside(int x,int y, Form *t){
  return (x >= t->get_x() 
	  && x < t->get_x() + t->get_l()
	  && y >= t->get_y()
	  && y < t->get_y() + t->get_h());
}


direction_t Collision::is_inside(Form *f, Form * t){
  bool inside_1 = is_inside(f->get_x()+ f->get_speed().m_x, f->get_y()+ f->get_speed().m_y, t);
  bool inside_2 = is_inside(f->get_x()+ f->get_l() +f->get_speed().m_x , f->get_y()+ f->get_speed().m_y, t);
  bool inside_3 = is_inside(f->get_x()+ f->get_speed().m_x, f->get_y() + f->get_h()+ f->get_speed().m_y, t);
  bool inside_4 = is_inside(f->get_x() + f->get_l()+ f->get_speed().m_x, f->get_y() + f->get_h()+ f->get_speed().m_y, t);
  if(inside_3 || inside_4)
    return SOUTH;
  else if(inside_4 || inside_2)
    return WEST;
  else if(inside_1 || inside_2)
    return NORTH;
  else if(inside_1 || inside_3)
    return EAST;
  else return NONE;
}

direction_t Collision::get_direction(){
  return m_direction;
  return SOUTH;
}

