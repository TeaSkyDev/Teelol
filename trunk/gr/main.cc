#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"


void routine(){

  Ecran sc(400,400);
  Event e;
  Character r("",50,20,20,10,&sc), r2("",20,200,300,10,&sc);
  vector <Character> c;
  for(int i = 0 ; i  < 25 ; i++)
    {
      c.push_back(Character("", i*10, i*15, 15,15,&sc));
      r.add_obstacle(c[i]);
    }
  r.add_obstacle(r2);
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
    sc.clean();
    r.show();
    r.pass_row();
    r2.show();

    for(int i = 0 ; i < c.size() ; i++)
      c[i].show();
    sc.Flip();
    SDL_Delay(50);
  }
}



int main(){
  routine();
  return 0;
}
