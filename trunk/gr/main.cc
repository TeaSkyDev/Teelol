#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"



void routine(){

  Ecran sc(700,500);

  Event e;
  Character r(I_TEE_P,50,20,10,10,&sc);
  Form f (20,200,300,10);
  f.set_screen(&sc);
  f.set_image(I_MUR);


  /* On ajoute le mur et la balle dans la liste de collisions */
  r << f;


  while(!e[QUIT]){
    e.UpdateEvent();
    if(e[LEFT])
      r.move_left();
    else if(e[RIGHT])
      r.move_right();
    else r.stop_x();
    if(e[JUMP]) {
      r.jump();
      e.reset_pressed(JUMP);
    }
    r.get_weapon()->set_angle(-atan2(e().m_x-r.get_x(), e().m_y-r.get_y())*180/M_PI + 90);
    r.get_weapon()->rotate(0, r.get_x() + r.get_l()/2, r.get_y() + r.get_h()/2, 0);
    if(e[LEFT_CL]){
      r.shoot();
    }
    
    sc.clean();
    r.pass_row();
    r.show();
    r.get_weapon()->show();
    f.show();
    sc.Flip();
    SDL_Delay(50);
  }

}



int main(){
  routine();
  return 0;
}
