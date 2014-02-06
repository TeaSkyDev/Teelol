#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"
#include "Parse.hh"
#include "Interface/Button.hh"
#include "Interface/Text.hh"
#include "Menu.hh"
#include "Interface/Focuser.hh"
#include "Interface/ScrollBar.hh"


void click(){
    cout << "signal clique recu" << endl;
}

void hover(){
    cout << "signal hover recu" << endl;
}

void focus(int i){
    cout << "champ texte " << i << " est focus" << endl;
}


void routine(){
    Focuser f;
    Ecran sc(400,400);
    ScrollBar b(10,10,200,10);
    b.add_lines(100);

    Event e; 
    while(!e[QUIT]){
	e.UpdateEvent();
	b.pass_row(e);
	b.show(&sc);
	sc.Flip();
	sc.clean();
	SDL_Delay(10);
    }
}



int main(){
  routine();
  return 0;
}

