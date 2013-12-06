#ifndef _COLL
#define _COLL



enum direction_t {
  NORTH = 1, SOUTH, EAST, WEST
};


class Collision{
public:
  Collision(Form * f, vector<Form> tab);
  Collision(Form * f, Form * t);
  direction_t get_direction();

private:
  bool is_inside(Form * f, Form * f);
  direction_t m_direction;

};



#endif 
