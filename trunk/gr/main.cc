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
#include "Interface/Label.hh"

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
    ListView lv(10,10,200,200,30);
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    lv.add_Item(new ListItem("salut"));
    lv.add_Item(new ListItem("slut"));
    
    Text t(10,220,10,200);
    NumberEdit ed(10,300,20,200,200,100);
    f.add_focusable(&t);
    f.add_focusable(&ed);
    f.add_focusable(&lv);
    t.focused.connect(f);
    ed.focused.connect(f);
    lv.focused.connect(f);


    while(!e[QUIT]){
	e.UpdateEvent();
	lv.pass_row(e);
	lv.show(&sc);
	t.pass_row(e);
	t.show(&sc);
	ed.pass_row(e);
	ed.show(&sc);
	f.pass_row(e);
	sc.Flip();
	sc.clean();
	SDL_Delay(50);
    }
}



int main(){
  routine();
  return 0;
}

