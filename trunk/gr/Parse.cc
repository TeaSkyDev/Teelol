#include "Parse.hh"


Parse::Parse(int x, int y):m_x(x), m_y(y){
}


point Parse::parse_this(Form * f,int x, int y){
  point p;
  cout<<m_x - x<<endl;
  p.x = (m_x - x) + f->get_x();
  p.y = (m_y - y) + f->get_y();
  return p;
}
