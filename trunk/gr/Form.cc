#include "Form.hh"



  void Form::set_image(string img){
    //temporaire
    if(img == "")
      m_surf = IMG_Load("../img/tee.png");
    else if(img == "Spew")
      m_surf = IMG_Load("../img/Spew.png");
    else if(img == "DMG")
      m_surf = IMG_Load("../img/DMG.png");
    else 
      m_surf = IMG_Load("../img/Health.png");

  }


  int Form::get_l(){ return m_l;}
  int Form::get_h(){ return m_h;}
  int Form::get_x(){ return m_x;}
  int Form::get_y(){ return m_y;}


void Form::show(){
    m_e->put(m_surf,m_x,m_y,m_h,m_l);
    m_e->Flip();
  }

  Form::~Form(){
    //  SDL_FreeSurface(m_surf);
  }

