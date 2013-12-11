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

  cout << "x = " << x << ", get_x = " << t->get_x() << endl;
  cout << "y = " << y << ", get_y = " << t->get_y() << endl;

  return (x >= t->get_x() 
	  && x < t->get_x() + t->get_l()
	  && y >= t->get_y()
	  && y < t->get_y() + t->get_h());
}


direction_t Collision::is_inside(Form *f, Form * t){
  /*bool inside_1 = is_inside(f->get_x(), f->get_y(), t);
  bool inside_2 = is_inside(f->get_x() + f->get_l(), f->get_y(), t);
  bool inside_3 = is_inside(f->get_x(), f->get_y() + f->get_h(), t);
  bool inside_4 = is_inside(f->get_x() + f->get_l(), f->get_y() + f->get_h(), t);
  if(inside_3 || inside_4)
    return SOUTH;
  else if(inside_4 || inside_2)
    return WEST;
  else if(inside_1 || inside_2)
    return NORTH;
  else if(inside_1 || inside_3)
    return EAST;
  else return NONE;*/

  Form f1(f->get_x() + 3, f->get_y(), 3, f->get_l() - 6); //nord
  Form f2(f->get_x() + 3, f->get_y() + f->get_h() - 3, 3, f->get_l() -6); //sud
  Form f3(f->get_x() + f->get_l() - 3, f->get_y() + 3, f->get_h() - 6, 3); //est
  Form f4(f->get_x(), f->get_y() + 3, 3, f->get_h() - 6); //ouest

  if(col(&f1, t)) {
    return NORTH;
  } else if(col(&f2, t)) {
    return SOUTH;
  } else if(col(&f3, t)) {
    return EAST;
  } else if(col(&f4, t)) {
    return WEST;
  } else {
    return NONE;
  }

}

bool Collision::col(Form * f, Form * t) {

  bool inside_1 = is_inside(f->get_x(), f->get_y(), t);
  bool inside_2 = is_inside(f->get_x() + f->get_l(), f->get_y(), t);
  bool inside_3 = is_inside(f->get_x(), f->get_y() + f->get_h(), t);
  bool inside_4 = is_inside(f->get_x() + f->get_l(), f->get_y() + f->get_h(), t);

  return (inside_1 || inside_2 || inside_3 || inside_4);

}

direction_t Collision::get_direction(){
  return m_direction;
  return SOUTH;
}

