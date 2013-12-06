#ifndef _CHAR
#define _CHAR

#include "Form.hh"

/*
*  attention a differencie la classe player de la classe Character 
*  la classe character est la classe uniquement d'affichage alors que la classe player permet de calculer la vie
*  les degat et autre 
*/

class Character: public Form{

public:
  
  Character(string img);

  void move_left();
  void move_right();
  void jump();
  void take_dmg(int);
  void take_life(int);
  void 

private:
 
  speed_t m_speed;//pour calculer la vitesse de deplacement des joueurs

  

};



#endif
