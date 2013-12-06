#include "Character.hh"



Character::Character(string img, int x, int y, int l, int h){
  m_x = x;
  m_y = y; 
  m_l = l; 
  m_h = h;
  set_image(img);
  m_img = img;
}

void Character::move_left(){
  m_speed.m_x = -1; 
}

void Character::move_right(){
  m_speed.m_x = 1;
}

void Character::stop_x(){
  m_speed.m_x = 0;
}

void Character::stop_y(){
  m_speed.m_y = 0;
}

void Character::jump(){
  //TODO
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
  if(m_wait > 0)
    m_wait--;
  if(m_wait == 0 and m_wrong_img)
    set_image(m_img);
}

