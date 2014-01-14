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
  void set_points(int p);
  void show_nick(); //affiche le nom au dessus du joueur
  void show_points(); //affiche les point du joueur
  std::string get_nick()const;
  int get_points()const;

  void win_point();  //Ajoute un point
  void loose_point();//Retire un point
  
private:
  std::string m_nick;
  int m_points;
  TTF_Font * m_font;

};

#endif
