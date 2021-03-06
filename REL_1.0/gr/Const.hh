#ifndef _CONST
#define _CONST

#include <iostream>
#include <fstream>
#include <map>
#include <SDL/SDL_ttf.h>

enum Image_t{
  I_TEE_P,
  I_TEE_PI,
  I_TEE_DMG,
  I_TEE_HEALTH,
  I_TEE_SPEW,
  I_TEE_DIE,
  I_TEE_A, 
  I_TEE_AI, 
  I_GRENADE, 
  I_GRENADE_I, 
  I_SHOTGUN, 
  I_SHOTGUN_I, 
  I_GRENADE_C,
  I_SHOTGUN_C,
  I_CART_EX,
  I_MUR,
  I_COEUR,
  I_EYES,
  I_CADRE,
  I_TEE_A_DMG,
  I_SOL,
  I_FOND
};


class Const{
public:
  Const(std::string);
  void load_file();
  std::string operator[](Image_t);
  TTF_Font * font();
  
private:
  std::string m_file;
  std::map<Image_t,std::string> m_path;
  TTF_Font * m_font;
}; 



#endif
