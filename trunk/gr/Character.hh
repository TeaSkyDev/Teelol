#ifndef _CHAR
#define _CHAR


#include "Form.hh"
#include "Collision.hh"
#include "Ammo.hh"
#include "Rotable.hh"
  /*
   *  attention a differencie la classe player de la classe Character 
   *  la classe character est la classe uniquement d'affichage alors que la classe player permet de calculer la vie
   *  les degat et autre 
   */


 
  class Character: public Form{

  public:
  
    Character(Image_t img, int, int , int , int , Ecran *);

    void set_position(unsigned int x, unsigned int y);
    void move_left();
    void move_right();
    void stop_x();
    void stop_y();
    void jump();
    void take_dmg();
    void take_life(int);
    void loose_life(int);
    void die();
    void spawn(int, int);
    void radical_move(int,int);
    void pass_row();
    void set_over_ground();
    void add_obstacle(Form *f);
    Character operator<<(Form & f);
    void shoot();
    collision_t collide();
    void show();
    void show_life();

    Rotable * get_weapon();
    type_t get_type();
    int get_life(){return m_life;}
    bool get_hurt();
    Ammo * get_ammo();
    void delete_obstacle(Form * f);
  private:
    void init_Weap();


  protected:
 

    Image_t m_img;
    int m_wait, m_dmg;
    bool m_ground; // vrai si le perso est sur le sol
    bool m_saut;
    vector <Form*> m_obstacle;
    Rotable * m_weapon;
    bool m_tomb;
    Ammo m_ammo;


    int m_life;

  };

#endif
