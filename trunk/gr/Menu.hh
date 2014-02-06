#ifndef _MENU
#define _MENU


#include "Ecran.hh"
#include "Event.hh"
#include <iostream>
#include "Interface/Button.hh"

enum Option{
  JOUER, QUITTER
};


class Menu{
public:
  
  
  Menu(Ecran *e);
  void start();
  Option getOption();
  
 


private:
  Ecran * m_e;
  
  Event m_event;
  Button * m_exit;
  Button * m_jouer;
  Option m_option;
};



#endif
