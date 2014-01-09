#include "Rotable.hh"



void Rotable::set_angle(double angle){
  if( angle > 0)
    m_angle = angle;
  else 
    m_angle = angle+360;
}

void Rotable::set_image(Image_t img){
  m_surf = IMG_Load(c[img].c_str());
  m_sauv = IMG_Load(c[img].c_str());
  if(img == 8)
    m_sauv2 = IMG_Load(c[(Image_t)9].c_str());    
  else if(img == 10)
    m_sauv2 = IMG_Load(c[(Image_t)11].c_str());    
  else m_sauv2 = m_sauv;
  m_l = m_surf->w;
  m_h = m_surf->h;

}


void Rotable::rotate_invacuo(double angle){
  SDL_Surface *s;
  if((m_angle < 270) && (m_angle >= 90))
    s = rotozoomSurface(m_sauv2 , -angle, 1.0, 1);
  else 
    s = rotozoomSurface(m_sauv, -angle, 1.0,1);
  if(m_surf){
    SDL_FreeSurface(m_surf);
  }
  m_surf = s;
}

void Rotable::rotate(double angle, int x, int y, int dist){
  m_angle += angle;
  SDL_Surface *s;
  if((m_angle < 270) && (m_angle >= 90))
    s = rotozoomSurface(m_sauv2 , -m_angle, 1.0, 1);
  else 
    s = rotozoomSurface(m_sauv, -m_angle, 1.0,1);
    if(m_surf){
    SDL_FreeSurface(m_surf);
  }
  m_surf = s;
  m_dist = dist;
  O.x = x;
  O.y = y;
  get_A();
  get_B();
  get_F();
  get_D();
  get_E();
  get_C();
  
  m_x = C.x;
  m_y = C.y;
  
}
 

double Rotable::get_angle(){return m_angle;}



void Rotable::get_A(){
  A.x = m_dist*cos(m_angle*M_PI / 180) + O.x;
  A.y = m_dist*(sin(m_angle*M_PI/180))  + O.y;
}

void Rotable::get_B(){
  B.x = A.x + (m_sauv->h/2)*(sin(m_angle*M_PI/180));
  B.y = A.y -  (m_sauv->h/2)*cos(m_angle*M_PI/180);

}

void Rotable::get_F(){
  F.x = A.x - (m_sauv->h/2)*sin(m_angle*M_PI/180);
  F.y = A.y + (m_sauv->h/2)*cos(m_angle*M_PI/180);
}

void Rotable::get_D(){
  D.x = B.x + (m_sauv->w)*cos(m_angle*M_PI/180);
  D.y = B.y + (m_sauv->w)*sin(m_angle*M_PI/180);

}

void Rotable::get_E(){
  E.x = D.x + (m_sauv->h)*(-sin(m_angle*M_PI/180));
  E.y = D.y +  (m_sauv->h)*cos(m_angle*M_PI/180);

}


void Rotable::get_C(){
  if(m_angle > 270 && m_angle <=360){
    C.y = D.y;
    C.x = B.x;
  }
  if(m_angle <= 270 && m_angle > 180){
    C.x = D.x;
    C.y = E.y;
  }
  if(m_angle <=180 && m_angle > 90){
    C.x = E.x;
    C.y = F.y;
  }
  if(m_angle > 0 && m_angle <= 90){
    C.x = F.x;
    C.y = B.y;
  }

}


int Rotable::get_xb(){
  return (E.x + D.x) / 2;
}

int Rotable:: get_yb(){
  return (E.y + D.y) / 2;
}

int Rotable::get_xba(){
  return D.x + cos((m_angle+35)*M_PI/180)*m_sauv->h;

}

int Rotable::get_yba(){
  return D.y + sin((m_angle+35)*M_PI/180)*m_sauv->h;


}

Rotable::~Rotable(){
  if(m_sauv){
    SDL_FreeSurface(m_sauv);
    m_sauv = NULL;
  }
  if(m_sauv2){
    SDL_FreeSurface(m_sauv2);
    m_sauv2 = NULL;
  }
}
