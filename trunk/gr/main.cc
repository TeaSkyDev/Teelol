#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"
#include "Parse.hh"
#include "Button.hh"
#include "Text.hh"

void routine(){
  
  Ecran sc(400,400);
  Button b("bonjour", 10,10,50,150);
  Text t(100,100,50,100);
  Event e; 
  while(!e[QUIT]){
    e.UpdateEvent();
    sc.clean();
    b.pass_row(e);

    t.pass_row();

    t.show(&sc);

    b.show(&sc);
    sc.Flip();

  }

}



int main(){
  routine();
  return 0;
}
