#include "Ecran.hh"

namespace gr{

  Ecran::Ecran(int hauteur, int largeur): height(hauteur), width(largeur){
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(height, width, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  }


  void Ecran::pause(){
    SDL_Event e;
    bool pause = true;
    while(pause){
      SDL_PollEvent(&e);
      if(e.key.keysym.sym == SDLK_SPACE)
	pause = false;
    }
  }

  void Ecran::Flip(){
    SDL_Flip(ecran);
  }

  void Ecran::put(SDL_Surface *s, int x, int y, int h, int l){
    SDL_Rect pos = {x,y,h,l};
    SDL_BlitSurface(s,NULL,ecran, &pos);
  }

  void Ecran::clean(){
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
  }

  Ecran::~Ecran(){
    SDL_Quit();
  }
};
