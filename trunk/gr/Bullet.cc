#include "Bullet.hh"


Bullet::Bullet(int x, int y, int h, int l, int dmg, string img):Form(x,y,h,l), m_dmg(dmg){
  set_image(img); 
}


int Bullet::get_dmg(){
  return m_dmg;
}

void Bullet::pass_row(){
  bool continuer = true;
  get_speed();
  for(int i = 0 ; i < abs(m_speed.m_y) ; i++){
    direction_t d = collide();
    if(d.col_y == NORTH || d.col_y == SOUTH){
      explode();
      continuer = false;
    }
    if(m_speed.m_y > 0)
      m_y++;
    else m_y--;
  }
  for (int i = 0 ; i < abs(m_speed.m_x) && continuer; i++){
    direction_t d = collide();
    if(d.col_x == EAST || d.col_x == WEST){
      explode();
    }
    if(m_speed.m_x > 0)
      m_x++;
    else
      m_x --;
  }
}

void Bullet::explode(){
  set_image("img/explosion.png");
  m_speed.m_x = 0;
  m_speed.m_y = 0;
}

void Bullet::add_obstacle(Form * f){
  m_obstacle.push_back(f);
}

direction_t Bullet::collide(){
  Collision c(this, m_obstacle);
  return c.get_direction();
}


void Bullet::set_speed(int angle){
  double angle = angle * Math.Pi / 180;
}
