#include "Form.hh"

Form::Form(int x, int y, int h, int l) : m_x(x), m_y(y), m_h(h), m_l(l) {}

  void Form::set_image(string img){
    //temporaire
    SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_h, 32,0,0,0,0);
    /* if(img == "")
      m_surf = IMG_Load("../img/tee.png");
    else if(img == "Spew")
      m_surf = IMG_Load("../img/Spew.png");
    else if(img == "DMG")
      m_surf = IMG_Load("../img/DMG.png");
    else 
      m_surf = IMG_Load("../img/Health.png");
    */
  }


  int Form::get_l(){ return m_l;}
  int Form::get_h(){ return m_h;}
  int Form::get_x(){ return m_x;}
  int Form::get_y(){ return m_y;}
speed_t Form::get_speed(){return m_speed;}

  void Form::show(){
    m_e->put(m_surf,m_x,m_y,m_h,m_l);
    
  }

  Form::~Form(){
    //  SDL_FreeSurface(m_surf);
  }

