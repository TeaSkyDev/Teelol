#include "Form.hh"

Form::Form(int x, int y, int h, int l) : m_x(x), m_y(y), m_h(h), m_l(l), c("../const/file") {
  m_surf = NULL;
  c.load_file();
}

void Form::set_image(Image_t img){
  m_wrong_img = false;
  m_surf = IMG_Load(c[img].c_str());
  m_img = img;
  m_h = m_surf->h;
  m_l = m_surf->w;
}



Image_t Form::get_img(){
  return m_img;
}


int Form::get_l(){ return m_l;}
int Form::get_h(){ return m_h;}
int Form::get_x(){ return m_x;}
int Form::get_y(){ return m_y;}
speed_t Form::get_speed(){return m_speed;}
type_t Form::get_type() {return FORM;}

void Form::loose_life(int l) {}

void Form::set_x(int x) {m_x = x;}
void Form::set_y(int y) {m_y = y;}





void Form::show(){
  SDL_Rect rect;
  rect.x = m_x;
  rect.y = m_y;
  rect.h = m_h;
  rect.w = m_l;
  m_e->put(m_surf,rect);
}


void Form::set_screen(Ecran * e){
  m_e = e;
}

Form::~Form(){
 
}

