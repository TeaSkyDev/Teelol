#ifndef _AMMO
#define _AMMO


#include "Bullet.hh"

enum cartridge_t{
  GRENADE,
  SHOTGUN
};

class Ammo{
public:

  Ammo();

  void shoot(Form * f, Ecran *e);
  void shoot(int, int, int, int);
  void pick_up(int);
  void set_type(cartridge_t);
  void pass_row();
  void show();
  void show_mun();
  void set_nb(int);
  void set_screen(Ecran * e);

  Bullet * operator[](int i);
  

  Bullet * get_exploded(int);
  int get_dmg();
  int get_NbAmmo();
  cartridge_t get_type();
  void add_obstacle(Form &);
  int get_max(){return m_ammo.size();}
  int get_explode_size(){return m_exploded.size();}
private:
  cartridge_t m_type;
  int m_num; // -1 = infini
  vector<Bullet> m_ammo, m_exploded;
  int m_max, m_dmg;
  int m_delay;
  vector<Form *> m_obstacle;
  Ecran * m_e;
  Const c;
};




#endif
