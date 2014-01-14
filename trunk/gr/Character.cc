#include "Character.hh"
#include "Collision.hh"

Character::Character(Image_t img, int x, int y, int l, int h, Ecran * e) : Form(x, y, h, l) {
  m_e = e;
  set_image(img);
  m_tomb = false;
  m_img = img;
  m_wrong_img = false;
  m_ground = true;
  m_speed.m_x = 0;
  m_speed.m_y = 0;
  m_saut = 2;
  init_Weap();
  init_eyes();
  m_ammo.set_nb(10);
  m_ammo.set_screen(e);
  m_ammo.add_obstacle(*this);
  m_life = 10;
  m_dmg = 0;
}

void Character::init_eyes(){
 m_eyes = new Rotable(m_x+1, m_y+1,10,10);
  m_eyes->set_image(I_EYES);
  m_eyes->set_screen(m_e);
}

void Character::init_Weap(){
  m_weapon = new Rotable(m_x+1, m_y+1,10,25);
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
  if(m_saut < 2){
    m_speed.m_y = -7; 
    m_saut++;
    m_y--;
  }
}

void Character::take_dmg(){
  set_image(I_TEE_DMG);
  m_wait = 10;//attend 10 tour avant de remettre l'image à la base 
  m_wrong_img = true;
}

void Character::take_life(int l){
  if(l + m_life >= 10) m_life = 10;
  else m_life += l;
}

void Character::loose_life(int l) {
  if(m_life > 0)
    m_life -= l;
  
  m_wrong_img = true;
  m_dmg = l;
}

void Character::pass_row(){
  m_ammo.pass_row();
  collision_t col = collide();
  Collision c(this, m_obstacle);
  Form * f = c.create_coly_Form(this);
  f->set_screen(m_e);
  if(m_e)
    f->show();
  m_speed.m_y = col.cor.m_y;
  m_speed.m_x = col.cor.m_x;
  m_x += m_speed.m_x;
  m_y += m_speed.m_y;
  
  if(col.dir.col_y == SOUTH){
    m_saut = 0;
    m_speed.m_y-=4;
  }
  if(col.type == ITEM){
    Item * it = (Item *)col.element;
    switch(it->get_item_type()){
    case AMMO:
      if(m_ammo.get_NbAmmo() != 10)
	m_ammo.pick_up(5);
      break;
    case LIFE:
      if(m_life != 10)
	take_life(5);
      break;
    }
  }

   if(m_speed.m_y < 50)
    m_speed.m_y ++;
}


void Character::die(){
  set_image(I_TEE_DIE);
}

void Character::spawn(int x, int y){
  m_x = x;
  m_y = y;
  set_image(m_img);
  m_ammo.set_nb(10);
  m_life = 10;
}


void Character::radical_move(int x, int y){
  m_x = x;
  m_y = y;
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



Rotable * Character::get_weapon(){
  return m_weapon;
}

type_t Character::get_type() {
  return CHARACTER;
}

bool Character::get_hurt(){
  int dmg = m_dmg;
  m_dmg = 0;
  return dmg;
}

Ammo * Character::get_ammo(){
  return &m_ammo;
}


void Character::shoot(){
  int id = 0;
  m_ammo.shoot(m_weapon, m_e, id);
}

void Character::move_eyes(){
  m_eyes->set_angle(m_weapon->get_angle());

  m_eyes->rotate(0,m_x + m_l/2, m_y + m_h/2,-5);
  //m_eyes->rotate_invacuo(-m_weapon->get_angle());
}


void Character::show(){
  //  m_ammo.show();
  move_eyes();
  SDL_Rect rect;
  rect.x = m_x;
  rect.y = m_y;
  rect.w = m_l;
  rect.h = m_h;
  m_e->put(m_surf,rect);
  m_eyes->show();
}

void Character::show_life(){
  SDL_Surface * coeur = IMG_Load(c[I_COEUR].c_str());
  SDL_Rect rect1;
  rect1.x = 10;
  rect1.y = 30;
  rect1.w = 10;
  rect1.h = 10;
  for(int i = 0 ; i <= m_life ; i++){
    m_e->put(coeur, rect1);
    rect1.x += 10 + coeur->w;
  }
  
}
Character Character::operator<<(Form & f){
  add_obstacle(&f);
  return *this;
}

void Character::delete_obstacle(Form * f) {
  for(int i = 0; i < m_obstacle.size(); i++) {
    if(m_obstacle[i] == f) {
      Form * tmp = m_obstacle[i];
      m_obstacle[i] = m_obstacle[m_obstacle.size()-1];
      m_obstacle.pop_back();
      delete tmp;
      break;
    }
  }
}

