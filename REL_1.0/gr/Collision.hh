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
  int dist_y;
  direction_e col_y;
  int dist_x;
};

/* Regroupe les directions de collision, le type d'élement avec laquelle la collision a eu lieu et un pointeur sur l'élément en question */
struct collision_t {
  direction_t dir;
  type_t      type;
  Form*       element;
  speed_t     cor;
};

class Collision{
public:
  Collision(Form * f, vector<Form*> tab);
  Collision(Form * f, Form * t);
  direction_t get_direction();
  collision_t get_collision();
  Form * create_coly_Form(Form *f);
  Form * create_colx_Form(Form * f);

private:

  void get_coly_hl(int &, int &,int&, int &, Form*);
  void get_colx_hl(int &, int &,int&, int &, Form*);
  direction_t get_coly_dir(Form * f, Form * t);
  direction_t get_colx_dir(Form * f, Form * t);

  direction_t is_inside(Form * f, Form * t);
  bool is_inside(int, int , Form * f);
  bool col(Form * f, Form * t);
  
  direction_t m_direction; 
  type_t      m_type; //type de la form avec laquelle a lieu l'obstacle
  Form*       m_element; //form avec laquelle a lieu l'obstacle
  speed_t m_cor;
};



#endif 
