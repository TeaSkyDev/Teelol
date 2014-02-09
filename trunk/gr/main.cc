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
#include "Interface/ListView.hh"
#include <sstream>
#include "Interface/TextNumber.hh"

using namespace std;
void foo(int purcent) {
    cout << purcent << endl;
}

void routine(){
    Focuser f;
    Ecran sc(400,400);
    TextNumber t(10,10,30,200);
    t.set_focus(true);
    cout << t.getId() << endl;
    Event e; 
    while(!e[QUIT]){
	e.UpdateEvent();
	t.pass_row(e);
	t.show(&sc);
	sc.Flip();
	sc.clean();
	SDL_Delay(10);
    }
    cout << t.getValue_int() << endl;
}



int main(){
  routine();
  return 0;
}

