#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"



void routine(){

  Ecran sc(400,400);

  Event e;
  Character r("../img/tee.png",50,20,10,10,&sc);
  Character f ("../img/Mur.png", 20,200,300,10, &sc);
  Character f2("../img/tee.png", 20,200,10,10,&sc);
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
    
    cout<<atan2(e().m_x-r.get_x(), e().m_y-r.get_y())*180/M_PI<<endl;
    f2.rotate_to(atan2(e().m_x-r.get_x(), e().m_y-r.get_y())*180/M_PI, r.get_x(), r.get_y(), 20);
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
