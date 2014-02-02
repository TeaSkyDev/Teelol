#include "Ia.hh"
using namespace std;

Ia::Ia(int x, int y, int h, int l) :Form(x,y,h,l) {
}

void Ia::die() {
}

void Ia::respawn() {
}

void Ia::shoot() {
}

void Ia::pass_row() {
}

collision_t Ia::collide(){
    Collision c(this, m_obstacle);
    return c.get_collision();
}

type_t Ia::get_type() {
    return IA;
}

void Ia::add_obstacle(Form * f) {
    m_obstacle.push_back(f);
}


void Ia::delete_obstacle(Form *f) {
    for(auto &it : m_obstacle) {
	if(it == f) {
	    Form * tmp = it;
	    it = *(m_obstacle.end() - 1);
	    m_obstacle.pop_back();
	    delete tmp;
	    break;
	}
    }
}
