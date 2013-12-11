#ifndef DEF_INPUT
#define DEF_INPUT

#include <SDL/SDL.h>

struct Input{
  char m_key[SDLK_LAST];
};

enum Mapp{
  LEFT, RIGHT, JUMP, QUIT , MAP_LAST
};


class Event {
public: 

  Event();

  void change_key(Mapp m, SDLKey k);
  void UpdateEvent();
  bool key_pressed(Mapp m);
  void reset_pressed(Mapp m);
  bool operator[](Mapp m);

private:
  Input m_in;
  SDLKey m_mapping[MAP_LAST];
  SDL_Event m_event;
  
};


#endif
