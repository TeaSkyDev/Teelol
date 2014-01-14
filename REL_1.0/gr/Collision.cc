#include "Collision.hh"

Collision::Collision(Form * f, vector <Form*> tab){
  m_direction.col_x = NONE;
  m_direction.col_y = NONE;
  m_direction.dist_y = 1000;
  m_direction.dist_x = 1000;
  m_type = TNONE;
  m_cor = f->get_speed();

  Form * fy = create_coly_Form(f);
  Form * fx = create_colx_Form(f);
  for(int i = 0 ; i < tab.size() ; i++){
    if(col(fy, tab[i])){
      direction_t t = get_coly_dir(f, tab[i]);
      if(m_direction.dist_y > t.dist_y){ 
	m_direction.col_y = t.col_y;  
	m_direction.dist_y = t.dist_y;
	m_cor.m_y = m_direction.dist_y;
	m_type    = tab[i]->get_type();
	m_element = tab[i];
      }
    }
    if(col(fx, tab[i])){
      direction_t t = get_colx_dir(f, tab[i]);
      if(m_direction.dist_x > t.dist_x){
	m_direction.col_x = t.col_x;  
	m_direction.dist_x = t.dist_x;
	m_cor.m_x = m_direction.dist_x;
	m_type    = tab[i]->get_type();
	m_element = tab[i];
      }
      }
    
  }
}




direction_t Collision::get_colx_dir(Form *f, Form * t){
  speed_t speed = f->get_speed();
  direction_t dir;
  if(speed.m_x <= 0 && f->get_x() > t->get_x()){
    dir.col_x = WEST;
    
    dir.dist_x = -(f->get_x() - (t->get_x() + t->get_l()));
  }
  else if(speed.m_x >= 0 && t->get_x() > f->get_x()){
    dir.col_x = EAST;
    
    dir.dist_x = t->get_x() - (f->get_x() + f->get_l());
  }
  else {
    dir.col_x = NONE;
    dir.dist_x = 10000;
  }
  return dir;
}


direction_t Collision::get_coly_dir(Form * f, Form * t){
  speed_t speed = f->get_speed();
  direction_t dir;
  if(speed.m_y <= 0 && f->get_y() + 1 > (t->get_y() + t->get_h())){
     dir.col_y = NORTH;
     dir.dist_y = -(f->get_y() - (t->get_y() + t->get_h()));
  }
  else if(speed.m_y >= 0 && t->get_y() + 1 > (f->get_y() + f->get_h())){
    dir.col_y = SOUTH;
    dir.dist_y = t->get_y() - (f->get_y() + f->get_h());
  }
  else{
    dir.col_x = NONE;
    dir.dist_x = 10000;
  }
  return dir;
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



void Collision::get_coly_hl(int &h, int &l,int &x, int &y, Form *f){
  speed_t speed = f->get_speed();

  if(speed.m_y > 0){
    h = f->get_h() + speed.m_y;
    y = f->get_y();

  }
  else if(speed.m_y < 0){
    h = f->get_h() - speed.m_y; 
    y = f->get_y() + speed.m_y;

  }
  else if(speed.m_y == 0){
    h = f->get_h();
    y = f->get_y();
  }
  x = f->get_x();
  l = f->get_h();
}


void Collision::get_colx_hl(int &h, int &l, int &x, int &y, Form *f){

  speed_t speed = f->get_speed();
 
  if(speed.m_x > 0){
    l = speed.m_x + f->get_l();
    x = f->get_x();
  }
  else{
    l = abs(speed.m_x) + f->get_l();
    x = f->get_x() - abs(speed.m_x);
  }
  y = f->get_y();
  h = f->get_h();
}


Form * Collision::create_colx_Form(Form * f){
  int h, l, x,y;
  get_colx_hl(h,l,x,y,f);
  return new Form(x,y,h,l);
}


Form * Collision::create_coly_Form(Form * f){
  int h, l, x, y;
  get_coly_hl(h,l,x,y, f);
  return new Form(x,y ,h,l);
}


direction_t Collision::is_inside(Form *f, Form * t) {
  Form f1(f->get_x() + 3, f->get_y() , 3, f->get_l() - 6); //nord
  Form f2(f->get_x() + 3, f->get_y() + f->get_h() - 3 , 3, f->get_l() - 6); //sud
  Form f3(f->get_x() + f->get_l() - 3, f->get_y() + 3, f->get_h() - 6 , 3); //est
  Form f4(f->get_x(), f->get_y() + 3 , f->get_h() - 6 , 3); //ouest

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

collision_t Collision::get_collision() {
  collision_t col;
  col.dir     = m_direction;
  col.type    = m_type;
  col.element = m_element;
  col.cor     = m_cor;
  return col;
}

