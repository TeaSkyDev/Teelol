#include "Ammo.hh"

Ammo::Ammo(): c("../const/file"){
  m_delay = 0;
  m_num = 10;
  m_max = 10;
  m_type = GRENADE;
  m_dmg = 5;
  c.load_file();
}

void Ammo::shoot(int x1, int x2, int y1, int y2){
  if((m_num > 0 || m_num == -1) && m_delay == 0){
    m_ammo.push_back(Bullet(x1,y1, 10,10,m_dmg,x2, y2, I_GRENADE_C));
    switch(m_type){
    case GRENADE:
      m_ammo[m_ammo.size()-1].set_image(I_GRENADE_C);break;
    case SHOTGUN:
      m_ammo[m_ammo.size()-1].set_image(I_SHOTGUN_C); break;
    default:
      m_ammo[m_ammo.size()-1].set_image(I_GRENADE_C); break;
    }
   
    for(int i = 0 ; i < m_obstacle.size() ; i++)
      m_ammo[m_ammo.size()-1].add_obstacle(m_obstacle[i]);
    if(m_num != -1)
      m_num --;
    m_delay = 10;
  }
}

void Ammo::shoot(Rotable * f, Ecran * e){
  if((m_num > 0 || m_num == -1) && m_delay == 0){

    m_ammo.push_back(Bullet(f->get_xb(), f->get_yb(), 10,10,m_dmg,f->get_xba(), f->get_yba(), I_GRENADE_C));
    switch(m_type){
    case GRENADE:
      m_ammo[m_ammo.size()-1].set_image(I_GRENADE_C);break;
    case SHOTGUN:
      m_ammo[m_ammo.size()-1].set_image(I_SHOTGUN_C); break;
    default:
      m_ammo[m_ammo.size()-1].set_image(I_GRENADE_C); break;
    }
    m_ammo[m_ammo.size()-1].set_screen(e);
    for(int i = 0 ; i < m_obstacle.size() ; i++)
      m_ammo[m_ammo.size()-1].add_obstacle(m_obstacle[i]);
    if(m_num != -1)
      m_num --;
    m_delay = 10;
  }

}

void Ammo::pick_up(int nb){
  if(m_num >= 0){
    m_num += nb;
  }
  if(m_num > m_max){
    m_num = m_max;
  }
}

void Ammo::set_nb(int nb){
  m_num = nb;
}

void Ammo::show(){
  for(int i = 0 ; i < m_ammo.size() ; i++){
    m_ammo[i].show();
  }
  for(int i = 0 ; i < m_exploded.size() ; i++){
    m_exploded[i].show();
  }
  show_mun();
}


void Ammo::show_mun(){
  SDL_Rect pos;
  pos.x = 10;
  pos.y = 10;
  SDL_Surface * mun;
  switch(m_type){
  case GRENADE:
    mun = IMG_Load(c[I_GRENADE_C].c_str()); break;
  case SHOTGUN:
    mun = IMG_Load(c[I_GRENADE_C].c_str()); break;
  }
  for(int i = 0 ; i < m_num ; i++){
    m_e->put(mun, pos);
    pos.x += 10+mun->w;
  }
}

void Ammo::set_type(cartridge_t type){
  m_type = type;
  switch(m_type){
  case GRENADE:
    m_dmg = 5; break;
  case SHOTGUN: 
    m_dmg = 2; break;
  }
}


void Ammo::pass_row(){
  for(int i = m_exploded.size() ; i > 0 ; i--)
    m_exploded.pop_back();

  for(int i = 0 ; i < m_ammo.size() ; i++){
    m_ammo[i].pass_row();
    if(m_ammo[i].get_exploded()){
      m_exploded.push_back(m_ammo[i]);
      m_exploded[m_exploded.size()-1].set_image(I_CART_EX);
      m_ammo[i] = m_ammo[m_ammo.size()-1];
      m_ammo.pop_back();
      i--;
    }
  }
  if(m_delay > 0)
    m_delay--;
}


Bullet * Ammo::operator[](int i){
  if(i < m_ammo.size() && i >= 0){
    return &m_ammo[i];
  }
  else return NULL;
}

Bullet * Ammo::get_exploded(int i){
  return &m_exploded[i];
}


int Ammo::get_dmg(){
   return m_dmg;
}

int Ammo::get_NbAmmo(){
  return m_num;
}


cartridge_t Ammo::get_type(){
  return m_type;
}

void Ammo::add_obstacle(Form &f){
  m_obstacle.push_back(&f);
}


void Ammo::set_screen(Ecran *e){
  m_e = e;
}
