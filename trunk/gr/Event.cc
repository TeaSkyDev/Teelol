#include "Event.hh"

Event::Event(){
  m_mapping[LEFT] = SDLK_q;
  m_mapping[RIGHT] = SDLK_d;
  m_mapping[JUMP] = SDLK_SPACE;
  m_mapping[QUIT] = SDLK_ESCAPE;
  m_mapping[TAB] = SDLK_TAB;
  m_mouse_mapping[LEFT_CL] = SDL_BUTTON_LEFT;
  m_mouse_mapping[RIGHT_CL] = SDL_BUTTON_RIGHT;
  m_in.m_key[m_mapping[JUMP]] = 0;
  m_in.m_key[m_mapping[LEFT]] = 0;
  m_in.m_key[m_mapping[RIGHT]] = 0;
  m_in.m_key[m_mapping[QUIT]] = 0;
  m_in.m_key[m_mapping[TAB]] = 0;
  m_in.m_mousebuttons[m_mouse_mapping[LEFT_CL]] = 0;
  m_wheel = 0;
  m_sensivity = 1;
}


void Event::change_key(Mapp m, SDLKey k){
  m_mapping[m] = k;
  m_in.m_key[k] = 0;
}


void Event::UpdateEvent(){
  while(SDL_PollEvent(&m_event)){
    if(m_event.type == SDL_KEYDOWN){
      m_in.m_key[m_event.key.keysym.sym] = 1;
    }
    if(m_event.type == SDL_KEYUP){
      m_in.m_key[m_event.key.keysym.sym] = 0;
    }  
    if(m_event.type == SDL_MOUSEMOTION){
      m_in.m_mouse_x = m_event.motion.x;
      m_in.m_mouse_y = m_event.motion.y;
      m_in.m_mouse_xrel = m_event.motion.yrel;
      m_in.m_mouse_yrel = m_event.motion.xrel;
    }
    if(m_event.type == SDL_MOUSEBUTTONDOWN){
      m_in.m_mousebuttons[m_event.button.button] = 1;
      if(m_event.button.button == SDL_BUTTON_WHEELUP){
	m_wheel += m_sensivity;
      }
      if(m_event.button.button == SDL_BUTTON_WHEELDOWN){
	m_wheel -= m_sensivity;
      }
    }
    if(m_event.type == SDL_MOUSEBUTTONUP){
      m_in.m_mousebuttons[m_event.button.button] = 0;
    }
  }
}

bool Event::key_pressed(Mapp m){
  return m_in.m_key[m_mapping[m]] == 1;
}


void Event::reset_pressed(Mapp m){
  m_in.m_key[m_mapping[m]] = 0;
}


char& Event::operator[](Mapp m){
  if(m <= QUIT)
    return m_in.m_key[m_mapping[m]];
  else
    return m_in.m_mousebuttons[m_mouse_mapping[m]];
}

position_t Event::operator()(){
  return {m_in.m_mouse_x, m_in.m_mouse_y};
}


int & Event::WheelChange(){
  return m_wheel;
}


SDL_Event & Event::getEvent(){
  return m_event;
}
