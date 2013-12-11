#include "Collision.hh"

Collision::Collision(Form * f, vector <Form> tab){
  m_direction.col_x = NONE;
  m_direction.col_y = NONE;
   for(int i = 0 ; i < tab.size() ; i++){
      direction_t t = is_inside(f, &tab[i]);
      if(t.col_y != NONE) {
        m_direction.col_y = t.col_y;  
      }
      if(t.col_x != NONE) {
        m_direction.col_x = t.col_x;  
      }
      
    }
}

Collision::Collision(Form * f, Form * t){
  //TODO
}

bool Collision::is_inside(int x,int y, Form *t){

  //cout << "x = " << x << ", get_x = " << t->get_x() << endl;
  // cout << "y = " << y << ", get_y = " << t->get_y() << endl;



  return (x >= t->get_x() 
	  && x < t->get_x() + t->get_l()
	  && y >= t->get_y()
	  && y < t->get_y() + t->get_h());
}


direction_t Collision::is_inside(Form *f, Form * t) {

  Form f1(f->get_x() + 3, f->get_y(), 3, f->get_l() - 6); //nord
  Form f2(f->get_x() + 3, f->get_y() + f->get_h() - 3, 3, f->get_l() -6); //sud
  Form f3(f->get_x() +4 + f->get_l() - 3, f->get_y() + 3, f->get_h() - 6, 3); //est
  Form f4(f->get_x() -4, f->get_y() + 3, 3, f->get_h() - 6); //ouest

  direction_t dir;

  if(col(&f1, t)) {
    dir.col_y = NORTH;
  } else if(col(&f2, t)) {
    dir.col_y = SOUTH;
  } else {
    dir.col_y = NONE;
  }

  if(col(&f3, t)) {
    dir.col_x = EAST;
  } else if(col(&f4, t)) {
    dir.col_x = WEST;
  } else {
    dir.col_x = NONE;
  }

  return dir;

}

bool Collision::col(Form * f, Form * t) {

  bool col_north = (f->get_y() + f->get_h()) <= t->get_y();
  bool col_south = f->get_y() >= (t->get_y() + t->get_h());
  bool col_east  = f->get_x() >= (t->get_x() + t->get_l());
  bool col_west  = (f->get_x() + f->get_l()) <= t->get_x();

  return !(col_north || col_south || col_east || col_west);

}

direction_t Collision::get_direction(){
  return m_direction; 
}

