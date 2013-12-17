#include "Event.hh"

Event::Event(){
  m_mapping[LEFT] = SDLK_LEFT;
  m_mapping[RIGHT] = SDLK_RIGHT;
  m_mapping[JUMP] = SDLK_SPACE;
  m_mapping[QUIT] = SDLK_ESCAPE;
  m_in.m_key[m_mapping[JUMP]] = 0;
  m_in.m_key[m_mapping[LEFT]] = 0;
  m_in.m_key[m_mapping[RIGHT]] = 0;
  m_in.m_key[m_mapping[QUIT]] = 0;
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
  }
}

bool Event::key_pressed(Mapp m){
  return m_in.m_key[m_mapping[m]] == 1;
}


void Event::reset_pressed(Mapp m){
  m_in.m_key[m_mapping[m]] = 0;
}


char& Event::operator[](Mapp m){
  return m_in.m_key[m_mapping[m]];
}
