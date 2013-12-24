#include "Character.hh"
#include "Collision.hh"

Character::Character(Image_t img, int x, int y, int l, int h, Ecran * e) : Form(x, y, h, l) {
  m_e = e;
  set_image(img);
  m_img = img;
  m_wrong_img = false;
  m_ground = true;
  m_speed.m_x = 0;
  m_speed.m_y = 0;
  m_saut = false;
  init_Weap();
  m_ammo.set_nb(10);
}

void Character::init_Weap(){
  m_weapon = new Form(m_x+1, m_y+1,10,25);
  m_weapon->set_image(I_GRENADE);
  m_weapon->set_screen(m_e);
  
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
  set_image(I_TEE_DMG);
  m_wait = 10;//attend 10 tour avant de remettre l'image à la base 
  m_wrong_img = true;
}

void Character::take_life(){
  set_image(I_TEE_HEALTH);
  m_wait = 10;
  m_wrong_img = true;
}

void Character::loose_life(int l) {
  m_life -= l;
}

void Character::pass_row(){
 
  m_ammo.pass_row();

  collision_t d = collide();

  if((d.dir.col_x == EAST && m_speed.m_x > 0) || (d.dir.col_x == WEST && m_speed.m_x < 0)) {
    m_speed.m_x *= -1;
  }

  bool iter = true;
  if(m_speed.m_y < 0) {
    m_y += m_speed.m_y;
  } else {
    for(int i = 0; i < m_speed.m_y; i++) {
      collision_t col = collide();
      if(col.dir.col_y != SOUTH) {

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
  set_image(I_TEE_DIE);
}

void Character::spawn(int x, int y){
  m_x = x;
  m_y = y;
  set_image(m_img);
}


void Character::radical_move(int x, int y){
  set_image(I_TEE_SPEW);
  m_wait = 10;
  m_wrong_img = true;
} 


void Character::set_over_ground(){
  m_ground = false;
}


void Character::add_obstacle(Form *f){
  m_obstacle.push_back(f);
  m_ammo.add_obstacle(*f);
}



collision_t Character::collide(){
  Collision c(this, m_obstacle);
  return c.get_collision();
}



Form * Character::get_weapon(){
  return m_weapon;
}

type_t Character::get_type() {
  return CHARACTER;
}


void Character::shoot(){
  m_ammo.shoot(m_weapon, m_e);
}

void Character::show(){
  m_ammo.show();
  SDL_Rect rect;
  rect.x = m_x;
  rect.y = m_y;
  rect.h = m_h;
  rect.w = m_l;
  m_e->put(m_surf,rect);
    
   

}


Character Character::operator<<(Form & f){
  add_obstacle(&f);
  return *this;
}


