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
    Focuser f;
    Ecran sc(400,400);
    Focuser s;
    NumberEdit t(10,10,20,100,900,100);
    NumberEdit t2(10,45,20,100,500,300);
    s.add_focusable(&t);
    s.add_focusable(&t2);
    t.focused.connect(s);
    t2.focused.connect(s);
    Button ok("OK", 10,100,30,100);
    Event e; 
    e.key_left.connect(do_left);
    e.key_right.connect(do_right);
    e.key_jump.connect(do_jump);
    e.key_quit.connect(do_quit);
    while(!e[QUIT]){
	e.UpdateEvent();
	t.pass_row(e);
	t.show(&sc);
	t2.pass_row(e);
	t2.pass_row(e);
	ok.pass_row(e);
	t2.show(&sc);
	ok.show(&sc);
	if(ok.getClicked()) {
	    sc.Resize(t.getValue(), t2.getValue());
	}
	sc.Flip();
	sc.clean();
	SDL_Delay(10);
    }
}



int main(){
  routine();
  return 0;
}

