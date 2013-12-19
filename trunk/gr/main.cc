#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"



void routine(){

  Ecran sc(700,500);

  Event e;
  Character r("../img/tee.png",50,20,10,10,&sc);
  Character f ("../img/Mur.png", 20,200,300,10, &sc);
  Character f2("../img/weap.png", 50,10,10,10,&sc);
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

      f2.set_angle(-atan2(e().m_x-r.get_x(), e().m_y-r.get_y())*180/M_PI + 90);
      f2.rotate(0, r.get_x() + r.get_l()/2, r.get_y() + r.get_h()/2, 0);

    sc.clean();
    r.pass_row();
    r.show();
    f.show();
    f2.show();
    sc.Flip();
    SDL_Delay(50);
  }

}



int main(){
  routine();
  return 0;
}
