#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "gr/Character.hh"
#include "gr/Ecran.hh"

/*
	Classe représentant un joueur 
*/

class Player : public Character {

	public:
  Player(std::string nick, Image_t img, int x, int y, int h, int l, Ecran * screen);
  
  void set_nick(std::string _nick);
  void show_nick();
  std::string get_nick()const;
  
	private:
		std::string m_nick;

};

#endif
