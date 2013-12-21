#include "Form.hh"

Form::Form(int x, int y, int h, int l) : m_x(x), m_y(y), m_h(h), m_l(l) {m_angle = 0;}

  void Form::set_image(string img){
    m_surf = IMG_Load(img.c_str());
    m_sauv = IMG_Load(img.c_str());
    m_sauv2 = IMG_Load("../img/2weap.png");    
  }


int Form::get_l(){ return m_l;}
int Form::get_h(){ return m_h;}
int Form::get_x(){ return m_x;}
int Form::get_y(){ return m_y;}

void Form::set_x(int x){ m_x = x;}
void Form::set_y(int y) {m_y = y;}
double Form::get_angle(){ return m_angle;}

void Form::set_angle(double angle){
  if( angle > 0)
    m_angle = angle;
  else 
    m_angle = angle+360;
}

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
  SDL_Surface *s;
  if((m_angle < 270) && (m_angle >= 90))
    s = rotozoomSurface(m_sauv2 , -m_angle, 1.0, 1);
  else 
    s = rotozoomSurface(m_sauv, -m_angle, 1.0,1);
  m_surf = s;
  m_x = x + dist * cos(m_angle*M_PI/180);
  m_y = y + dist * sin(m_angle*M_PI/180);
  recalibrate();
}

void Form::recalibrate(){

  if(m_angle > 175 && m_angle < 185){
    m_x -= m_surf->w;
    m_y -= m_surf->h/2;
   
  }
  if(m_angle > 265 && m_angle < 275){
    m_x -= m_surf->w/2;
    m_y -= m_surf->h;
  }
  if((m_angle < 5 && m_angle > 0) || (m_angle > 355 && m_angle < 360)){
    m_y -= m_surf->h/2;
  }
  if(m_angle > 80 && m_angle < 95){
    m_x -= m_surf->w/2;
  }
  if(m_angle >= 95 && m_angle <= 175){
    m_x -= m_surf->w;
  }
  if(m_angle >= 185 && m_angle <= 265){
    m_x -= m_surf->w;
    m_y -= m_surf->h;
  }
  if(m_angle >= 275 && m_angle <= 355){
    m_y -= m_surf->h;
  }
    
    
}


int Form::get_xb(){

  if(m_angle > 175 && m_angle < 185){
    return m_x;
  }
  if(m_angle > 265 && m_angle < 275){
    return  m_x;
  }
  if((m_angle < 5 && m_angle > 0) || (m_angle > 355 && m_angle < 360)){
    return m_x+m_surf->w;
  }
  if(m_angle > 80 && m_angle < 95){
    return m_x + m_surf->w/2;
  }
  if(m_angle >= 95 && m_angle <= 175){
    return m_x;
  }
  if(m_angle >= 185 && m_angle <= 265){
    return m_x;

  }
  if(m_angle >= 275 && m_angle <= 355){
    return m_x+m_surf->w;
  }
  return m_x+m_surf->w;


}

int Form::get_yb(){
  
  if(m_angle > 175 && m_angle < 185){
    return m_y + m_surf->h/2;
  }
  if(m_angle > 265 && m_angle < 275){
    return  m_y;
  }
  if((m_angle < 5 && m_angle > 0) || (m_angle > 355 && m_angle < 360)){
    return m_y + m_surf->h/2;
  }
  if(m_angle > 80 && m_angle < 95){
    return m_y + m_surf->h;
  }
  if(m_angle >= 95 && m_angle <= 175){
    return m_y+m_surf->h;
  }
  if(m_angle >= 185 && m_angle <= 265){
    return  m_y;
  }
  if(m_angle >= 275 && m_angle <= 355){
    return m_y;
  }
  return m_y + m_surf->h;
  

}

int Form::get_yba(){
  if(m_angle > 175 && m_angle < 185){
    return m_y + m_surf->h/2;
  }
  if(m_angle > 265 && m_angle < 275){
    return  m_y - 5;
  }
  if((m_angle < 5 && m_angle > 0) || (m_angle > 355 && m_angle < 360)){
    return m_y + m_surf->h/2;
  }
  if(m_angle > 80 && m_angle < 95){
    return m_y + m_surf->h + 5;
  }
  if(m_angle >= 95 && m_angle <= 175){
    return m_y+m_surf->h+5;
  }
  if(m_angle >= 185 && m_angle <= 265){
    return  m_y - 5;
  }
  if(m_angle >= 275 && m_angle <= 355){
    return m_y - 5;
  }
  return m_y + m_surf->h + 5;
  
}

int Form::get_xba(){
  
  
  if(m_angle > 175 && m_angle < 185){
    return m_x - 5;
  }
  if(m_angle > 265 && m_angle < 275){
    return  m_x;
  }
  if((m_angle < 5 && m_angle > 0) || (m_angle > 355 && m_angle < 360)){
    return m_x+m_surf->w + 5;
  }
  if(m_angle > 80 && m_angle < 95){
    return m_x + m_surf->w/2;
  }
  if(m_angle >= 95 && m_angle <= 175){
    return m_x - 5;
  }
  if(m_angle >= 185 && m_angle <= 265){
    return m_x - 5;

  }
  if(m_angle >= 275 && m_angle <= 355){
    return m_x+m_surf->w + 5;
  }
  return m_x+m_surf->w + 5;

}


void Form::rotate_to(double angle, int x, int y, int dist){
  double _angle = m_angle - angle;
  SDL_Surface * s = rotozoomSurface(m_sauv, -_angle, 1.0,1);
  m_surf = s;
  m_x = x + dist * cos(_angle * M_PI/180);
  m_y = y + dist * sin(_angle*M_PI/180);

}

void Form::set_screen(Ecran * e){
  m_e = e;
}

  Form::~Form(){
    //  SDL_FreeSurface(m_surf);
  }

