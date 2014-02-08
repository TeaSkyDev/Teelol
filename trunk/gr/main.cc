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
using namespace std;
void foo(int purcent) {
    cout << purcent << endl;
}

void routine(){
    Focuser f;
    Ecran sc(400,400);
    ListView lv(10,40,200,200,30);
    string text = "Item";
    for (int i = 0 ; i < 10 ; i++) {
	stringstream ss;
	ss << text << " " << i;
	cout << ss.str() << endl;
	lv.add_Item(new ListItem(ss.str()));
    }
    Event e; 
    while(!e[QUIT]){
	e.UpdateEvent();
	lv.pass_row(e);
	lv.show(&sc);
	sc.Flip();
	sc.clean();
	SDL_Delay(10);
    }
    cout << lv.selected()->text() << endl;
}



int main(){
  routine();
  return 0;
}

