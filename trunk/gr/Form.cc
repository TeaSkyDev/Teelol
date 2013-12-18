#include "Form.hh"

Form::Form(int x, int y, int h, int l) : m_x(x), m_y(y), m_h(h), m_l(l) {}

  void Form::set_image(string img){
    m_surf = IMG_Load(img.c_str());
    m_sauv = IMG_Load(img.c_str());
  }


int Form::get_l(){ return m_l;}
int Form::get_h(){ return m_h;}
int Form::get_x(){ return m_x;}
int Form::get_y(){ return m_y;}
void Form::set_x(int x){ m_x = x;}
void Form::set_y(int y) {m_y = y;}

int Form::x_to_sig(){ return boost::lexical_cast<int>(m_x);}
int Form::y_to_sig(){ return boost::lexical_cast<int>(m_y);}
int Form::h_to_sig(){ return boost::lexical_cast<int>(m_h);}
int Form::l_to_sig(){ return boost::lexical_cast<int>(m_l);}


speed_t Form::get_speed(){return m_speed;}

  void Form::show(){
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.h = m_h;
    rect.w = m_l;
    m_e->put(m_surf,rect);
    
   
    
  }


void Form::rotate(double angle, int x, int y, int dist){
  m_angle += angle;
  SDL_Surface * s = rotozoomSurface(m_sauv , -m_angle, 1.0, 1);
  m_surf = s;
  m_x = x + dist * cos(m_angle*M_PI/180);
  m_y = y + dist * sin(m_angle*M_PI/180);
}


void Form::set_screen(Ecran * e){
  m_e = e;
}

  Form::~Form(){
    //  SDL_FreeSurface(m_surf);
  }

