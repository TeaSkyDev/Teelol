#include "Parse.hh"


Parse::Parse(int x, int y):m_x(x), m_y(y){
}


point Parse::parse_this(Form * f,int x, int y){
  point p;
  p.x = (m_x - x) + f->get_x();
  p.y = (m_y - y) + f->get_y();
  return p;
}


point Parse::inv_parse_this(int x, int y ,int o_x, int o_y){
  point p;
  p.x = x - (m_x - o_x);
  p.y = y - (m_y - o_y);
  return p;
}
