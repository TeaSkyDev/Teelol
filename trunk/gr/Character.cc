#include "Character.hh"
#include "Collision.hh"

Character::Character(string img, int x, int y, int l, int h, Ecran * e){
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
    
    if(m_wait > 0)
      m_wait--;
    if(m_wait == 0 and m_wrong_img){
      set_image(m_img);
      m_wrong_img = false;
    }
    m_x += m_speed.m_x;
    m_y += m_speed.m_y;

    if(! m_ground)
      m_speed.m_y ++;
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

  direction_t Character::collide(vector <Form> tab){
    Collision c(this, tab);
    return c.get_direction();
  }

