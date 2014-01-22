#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"
#include "Parse.hh"
#include "Button.hh"
#include "Text.hh"

void routine(){
  
  Ecran sc(400,400);
  Button b("valider", 10,10,50,150);
  Text t(100,100,50,100);
  Event e; 
  while(!b.getClicked() && !t.Validated()){
    e.UpdateEvent();
    sc.clean();
    b.pass_row(e);
    t.pass_row(&e.getEvent());
    t.show(&sc);
    b.show(&sc);
    sc.Flip();
    SDL_Delay(50);
  }
  cout<<t.getText() << endl;
}



int main(){
  routine();
  return 0;
}
