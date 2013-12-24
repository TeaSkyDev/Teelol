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
  void pick_up(int);
  void set_type(cartridge_t);
  void pass_row();
  void show();
  void show_mun();
  void set_nb(int);
  void set_screen(Ecran * e);

  int get_dmg();
  int get_NbAmmo();
  cartridge_t get_type();
  void add_obstacle(Form &);


private:
  cartridge_t m_type;
  int m_num; // -1 = infini
  vector<Bullet> m_ammo;
  int m_max, m_dmg;
  int m_delay;
  vector<Form *> m_obstacle;
  Ecran * m_e;
  Const c;
};




#endif
