#include "Ecran.hh"

Ecran::Ecran(int hauteur, int largeur): height(hauteur), width(largeur), c("../const/file"){
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

  void Ecran::put(SDL_Surface *s, SDL_Rect r){
    /*    SDL_Surface *surf = SDL_CreateRGBSurface(SDL_HWSURFACE,r.w,r.h,32,0,0,0,0);
    SDL_FillRect(surf, NULL, SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(surf,NULL,ecran, &r);*/
    SDL_BlitSurface(s,NULL,ecran, &r);
  }

  void Ecran::clean(){
    SDL_Rect rect = {0,0,0,0};
    //SDL_BlitSurface(m_fond, NULL, ecran, &rect);
    //SDL_Flip(ecran);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
  }

  void Ecran::Resize(int hauteur, int largeur){
    SDL_FreeSurface(ecran);
    height = hauteur;
    width = largeur;
    ecran = SDL_SetVideoMode(height, width, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  }

int Ecran::get_l(){
  return ecran->w;
}

int Ecran::get_h(){
  return ecran->h;
}
  
  Ecran::~Ecran(){
    SDL_FreeSurface(ecran);
    SDL_Quit();
  }

 
