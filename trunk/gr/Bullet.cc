#include "Bullet.hh"


Bullet::Bullet(int x, int y, int h, int l, int dmg, int x_s, int y_s, Image_t img):Form(x,y,h,l), m_dmg(dmg) {

  set_image(img); 
  //m_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, h, l, 32, 0, 0, 0, 0);
  exploded = false;
  m_killed = NULL;
  m_vy  = 0;
  m_vx  = 0;
  m_x_init = x_s;
  m_y_init = y_s;
  int o = m_x_init - m_x;
  int p = m_y_init - m_y;
  m_angle = atan2(p,o);
  int speed_init = sqrt(o*o+p*p);

  m_vx = speed_init*cos(m_angle);
  m_vy = speed_init*sin(m_angle);

}


int Bullet::get_dmg(){
  return m_dmg;
}

type_t Bullet::get_type() {
  return BULLET;
}

void Bullet::pass_row(){

  double g  = 9.81;
  m_vy+=0.5;

  m_temps += 8;

  bool continuer = true;

  for(int i = 0 ; i < abs((int)m_vy) ; i+=3){
    collision_t d = collide();
    if((d.dir.col_y == NORTH || d.dir.col_y == SOUTH) && d.type != ITEM){
      if(d.type == CHARACTER) {
	d.element->loose_life(m_dmg);
	m_killed = d.element;
       
      }
      explode();
      continuer = false;
      break;
    }
   
    if(m_vy > 0)
      m_y +=3;
    else m_y -=3;
  }

  for(int i = 0 ; i < abs((int)m_vx) && continuer; i+=3){
    collision_t d = collide();
    if((d.dir.col_x == EAST || d.dir.col_x == WEST) && d.type != ITEM){
      if(d.type == CHARACTER) {
	d.element->loose_life(m_dmg);
	m_killed = d.element;
      }
      explode();
      break;
    }

    if(m_vx > 0)
      m_x +=3;
    else
      m_x -=3;
  }
  if(m_x > 600){
    m_x = 0;
  } 
  if(m_y > 600){
    m_y = 0;
  }
  if(m_x + m_l < 0)
    m_x = 600;
}

void Bullet::explode(){
  set_image(I_CART_EX);

  m_speed.m_x = 0;
  m_speed.m_y = 0;
  exploded = true;
}

void Bullet::add_obstacle(Form * f){
  m_obstacle.push_back(f);
}

collision_t Bullet::collide(){
  Collision c(this, m_obstacle);
  return c.get_collision();
}


void Bullet::set_speed(int temps){
  //double angle = angle * Math.Pi / 180;
  //double angle = angle * 3.1415 / 180;

  double angle = m_angle * M_PI / 180; //50° en radians 
  m_speed.m_x *= cos(angle);
  m_speed.m_y *= -sin(angle);
  double g     = 10;

  m_speed.m_y += g * temps;
  m_x         += m_speed.m_x * temps;
  m_y         += m_speed.m_y * temps;


}



bool Bullet::get_exploded(){
  return exploded;
}

Form* Bullet::get_killed() {
  return m_killed;
}

void Bullet::set_killed(Form * f) {
  m_killed = f;
}
