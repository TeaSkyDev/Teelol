#include "Ammo.hh"

Ammo::Ammo(){
  m_delay = 0;
  m_num = 10;
  m_type = GRENADE;
  m_dmg = 5;
}
void Ammo::shoot(Form * f, Ecran * e){
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
  for(int i = 0 ; i < m_ammo.size() ; i++){
    m_ammo[i].pass_row();
    if(m_ammo[i].get_exploded()){
      m_ammo[i] = m_ammo[m_ammo.size()-1];
      m_ammo.pop_back();
      i--;
    }
  }
  if(m_delay > 0)
    m_delay--;
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
