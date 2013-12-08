#ifndef _CHAR
#define _CHAR


#include "Form.hh"
#include "Collision.hh"
  /*
   *  attention a differencie la classe player de la classe Character 
   *  la classe character est la classe uniquement d'affichage alors que la classe player permet de calculer la vie
   *  les degat et autre 
   */


 
  class Character: public Form{

  public:
  
    Character(string img, int, int , int , int , Ecran *);

    void move_left();
    void move_right();
    void stop_x();
    void stop_y();
    void jump();
    void take_dmg();
    void take_life();
    void die();
    void spawn(int, int);
    void radical_move(int,int);
    void pass_row();
    void set_over_ground();

    direction_t collide(vector<Form> tab);//prend en entree un tableau d'obstacle

  private:
 
    speed_t m_speed;//pour calculer la vitesse de deplacement des joueurs
    string m_img;
    int m_wait;
    bool m_wrong_img;
    bool m_ground; // vrai si le perso est sur le sol
  };

#endif
