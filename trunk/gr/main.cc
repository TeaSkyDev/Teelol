#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"

void routine(){

  Ecran sc(400,400);
  Event e;
  Character r("../img/tee.png",50,20,10,10,&sc);
  Character f ("../img/Mur.png", 20,200,300,10, &sc);
  r.add_obstacle(&f);
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
    cout<<e().m_x<< " " << e().m_y<<endl;
    sc.clean();
    r.show();
    r.pass_row();
    f.show();
    sc.Flip();
    SDL_Delay(50);
  }
}



int main(){
  routine();
  return 0;
}
