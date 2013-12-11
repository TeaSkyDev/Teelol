#include "Character.hh"
#include "Collision.hh"

Character::Character(string img, int x, int y, int l, int h, Ecran * e) : Form(x, y, h, l) {
  m_x = x;
  m_y = y; 
  m_l = l; 
  m_h = h;
  m_e = e;
  set_image(img);
  m_img = img;
  m_wrong_img = false;
  m_ground = true;
  m_speed.m_x = 0;
  m_speed.m_y = 0;
  m_saut = false;
}


void Character::set_position(unsigned int x, unsigned int y){
  m_x = x;
  m_y = y;
}


void Character::move_left(){
  m_speed.m_x = -5; 
}

void Character::move_right(){
  m_speed.m_x = 5;
}

void Character::stop_x(){
  m_speed.m_x = 0;
}

void Character::stop_y(){
  m_speed.m_y = 0;
  m_ground = true;
}

void Character::jump(){
  m_ground = false;
  m_speed.m_y = -5; 
  m_saut = true;
  m_y--;
}

void Character::take_dmg(){
  set_image("Dmg"+m_img);
  m_wait = 10;//attend 10 tour avant de remettre l'image à la base 
  m_wrong_img = true;
}

void Character::take_life(){
  set_image("Health"+m_img);
  m_wait = 10;
  m_wrong_img = true;
}

void Character::pass_row(){
  cout<<"ici :"<<m_x<<" "<<m_y<<" "<<m_speed.m_x<<" "<< m_speed.m_y<<endl;
  /*
    if(m_wait > 0)
    m_wait--;
    if(m_wait == 0 and m_wrong_img){
    set_image(m_img);
    m_wrong_img = false;
    }*/
  
  direction_t d = collide();

  if((d.col_x == EAST && m_speed.m_x > 0) || (d.col_x == WEST && m_speed.m_x < 0)) {
    m_speed.m_x = 0;
  }

  bool iter = true;
  if(m_speed.m_y < 0) {
    m_y += m_speed.m_y;
  } else {
    for(int i = 0; i < m_speed.m_y; i++) {
      direction_t col = collide();
      cout << "col y = " << col.col_y << endl;
      if(col.col_y != SOUTH) {
        m_y++;
      }
      else {
	m_speed.m_y = 0;
	iter = false;}
    }
  }
  
  m_x += m_speed.m_x;
  if(iter)
    m_speed.m_y++;
  
}

void Character::die(){
  set_image("Die"+m_img);
}

void Character::spawn(int x, int y){
  m_x = x;
  m_y = y;
  set_image(m_img);
}


void Character::radical_move(int x, int y){
  set_image("Spew"+m_img);
  m_wait = 10;
  m_wrong_img = true;
} 


void Character::set_over_ground(){
  m_ground = false;
}


void Character::add_obstacle(Form f){
  m_obstacle.push_back(f);
}



direction_t Character::collide(){
  Collision c(this, m_obstacle);
  return c.get_direction();
}

