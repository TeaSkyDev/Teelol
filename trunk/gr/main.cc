#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"
#include "Parse.hh"
#include "Button.hh"
#include "Text.hh"
#include "Menu.hh"

void routine(){
  
  Ecran sc(400,400);
  Button b("bonjour", 10,10,50,150);
  Text t(100,100,50,100);
  Event e; 
  Menu m(&sc);
  m.start();
  cout<<m.getOption();
}



int main(){
  routine();
  return 0;
}

