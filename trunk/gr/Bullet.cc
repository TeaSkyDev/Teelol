#include "Bullet.hh"


Bullet::Bullet(int x, int y, int h, int l, int dmg, string img):Form(x,y,h,l), m_dmg(dmg){
  set_image(img); 
}


int Bullet::get_dmg(){
  return m_dmg;
}
