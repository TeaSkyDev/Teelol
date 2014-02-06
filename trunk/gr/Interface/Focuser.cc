#include "Focuser.hh"
using namespace std;

void Focuser::operator()(int id) {
    for(auto it: m_focusable) {
	if(it->getId() != id) {
	    it->set_focus(false);
	}
    }
}


void Focuser::add_focusable(Text * t){
    m_focusable.push_back(t);
    //t->set_focus(true);
}
