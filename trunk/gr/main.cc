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
#include "Interface/NumberEdit.hh"

using namespace std;
void foo(int purcent) {
    cout << purcent << endl;
}


void do_left() {
    cout << "appuie sur left" << endl;
}


void do_right() {
    cout << "appuie sur right" << endl;
}

void do_jump() {
    cout << "appuie sur jump" << endl;
}

void do_quit() {
    cout << "appuie sur quit" << endl;
}

void routine(){
    Event e;
    Ecran sc(400,400);
    Focuser f;
    Text t(10,10,20,300);
    f.add_focusable(&t);
    t.focused.connect(f);
    while(!e[QUIT]){
	e.UpdateEvent();
	t.pass_row(e);
	t.show(&sc);
	sc.Flip();
	sc.clean();
	SDL_Delay(50);
    }
}



int main(){
  routine();
  return 0;
}

