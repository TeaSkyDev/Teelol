#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"


void routine(){

  Ecran sc(400,400);
  Event e;
  Character r("",10,10,10,10,&sc), r2("",20,380,300,10,&sc);
  r.add_obstacle(r2);
  while(!e[QUIT]){
    e.UpdateEvent();
    if(e[LEFT])
      r.move_left();
    else if(e[RIGHT])
      r.move_right();
    else r.stop_x();
    if(e[JUMP])
      r.jump();
    sc.clean();
    r.show();
    r.pass_row();
    r2.show();
    sc.Flip();
    SDL_Delay(20);
  }
}



int main(){
  routine();
  return 0;
}
