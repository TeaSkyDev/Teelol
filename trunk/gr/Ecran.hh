#ifndef _Ecran
#define _Ecran

#include <SDL/SDL.h>




  class Ecran{
    
  public:
    Ecran(int hauteur, int largeur);
    void Resize(int hauteur, int largeur);
    void pause();
    void Flip();
    void put(SDL_Surface * s, SDL_Rect r); 
    void clean();
    int get_h();
    int get_l();
    ~Ecran();
  private:
  
    SDL_Surface * ecran;
    int height, width;
    
  };

#endif
