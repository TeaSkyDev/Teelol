#ifndef _PARSE_
#define _PARSE_

#include "Form.hh"


class Parse{
public:
  
  Parse(int, int);
  point parse_this(Form * s, int , int);
  


private:
  int m_x, m_y;
  int m_s_h, m_s_l;
};


#endif
