#ifndef _COLL
#define _COLL

#include <iostream>
#include <vector>
#include "Form.hh"
using namespace std;

enum direction_e {
  NORTH = 1, SOUTH, EAST, WEST, NONE
};

struct direction_t {
	direction_e col_x;
	direction_e col_y;
};

/* Regroupe les directions de collision et le type d'élement avec laquelle la collision a eu lieu */
struct collision_t {
	direction_t dir;
	type_t      type;
};

class Collision{
public:
  Collision(Form * f, vector<Form*> tab);
  Collision(Form * f, Form * t);
  direction_t get_direction();
  collision_t get_collision();

private:
  direction_t is_inside(Form * f, Form * t);
  bool is_inside(int, int , Form * f);
  bool col(Form * f, Form * t);
  
  direction_t m_direction;
  type_t      m_type;

};



#endif 
