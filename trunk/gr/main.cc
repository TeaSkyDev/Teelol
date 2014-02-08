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

void foo(int purcent) {
    cout << purcent << endl;
}

void routine(){
    Focuser f;
    Ecran sc(400,400);
    ListView lv(10,10,200,200,20);
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    lv.add_Item(new ListItem("salut les mec"));   
    Event e; 
    while(!e[QUIT]){
	e.UpdateEvent();
	lv.pass_row(e);
	lv.show(&sc);
	sc.Flip();
	sc.clean();
	SDL_Delay(10);
    }
}



int main(){
  routine();
  return 0;
}

