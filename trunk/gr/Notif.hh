#ifndef DEF_NOTIF
#define DEF_NOTIF

/*
==========================================================
Classe gérant toutes les notifications du jeu à afficher
afin d'informer le joueur des différents évènements
==========================================================
 */

#include "Ecran.hh"
#include "SDL/SDL_ttf.h"

class Notif {
public:
  Notif(Ecran * ec);
  
  void pass_row();
  void add_notif(const char * str);

private:
  Ecran *m_ecran;
  SDL_Surface *m_surf;
  SDL_Rect m_rect;
  SDL_Color m_color;
  TTF_Font *m_police;
  int m_rows_init;
  int m_rows;
};

#endif
