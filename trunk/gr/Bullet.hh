#ifndef _BULLET
#define _BULLET

#include "Form.hh"
#include "Collision.hh"
#include <vector>
#include <math.h>

class Bullet: public Form{
public:
  Bullet(int x, int y, int h, int l, int dmg, int , int, Image_t img);
  int get_dmg();
  type_t get_type();
  void pass_row();
  void explode();
  void add_obstacle(Form * f);
  collision_t collide();
  void set_speed(int temps); //calcule la vitesse a laquelle va devoir aller la balle

  bool get_exploded();
  Form* get_killed(); //Renvoie un pointeur sur le joueur tué
  void set_killed(Form *);

private:
  int m_dmg;
  double m_angle;
  int m_speed_init;
  int m_temps;
  bool exploded;
  Form* m_killed; //contient le joueur tué, sinon NULL
  vector<Form *> m_obstacle;

  /* tmp */
  double m_vx;
  double m_vy;
  int m_x_init;
  int m_y_init;
};




#endif
