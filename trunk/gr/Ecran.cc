#include "Ecran.hh"

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
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_Surface *s2 = SDL_CreateRGBSurface(SDL_HWSURFACE, l,h,32,0,0,0,0);
    SDL_FillRect(s2, NULL, SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(s2,NULL,ecran, &pos);
  }

  void Ecran::clean(){
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
  }

  void Ecran::Resize(int hauteur, int largeur){
    SDL_FreeSurface(ecran);
    height = hauteur;
    width = largeur;
    ecran = SDL_SetVideoMode(height, width, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  }
  
  Ecran::~Ecran(){
    SDL_FreeSurface(ecran);
    SDL_Quit();
  }

