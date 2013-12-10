#include "Ecran.hh"
#include "Character.hh"
#include "Event.hh"

void routine(){
  Ecran sc(300,300);
  string action;
  Character r("",10,10,10,10,&sc);
  Character r2("",10,290,300,10,&sc);
  r.add_obstacle(r2);
  Event e;
  while(1){
    e.UpdateEvent();
    if(e.key_pressed(LEFT))
	r.move_left();
    else if(e.key_pressed(RIGHT))
	r.move_right();
    else if(!e.key_pressed(LEFT) && !e.key_pressed(RIGHT))
      r.stop_x();
    if(e.key_pressed(JUMP)){
      r.jump();
      e.reset_pressed(JUMP);
    }
    if(e.key_pressed(QUIT))
      break;
    r.pass_row();
    r.show();
    
    r2.show();
    // r3.show();
    sc.clean();
    SDL_Delay(50);
  }

}



int main()
{
  routine();
  return 0;
}
