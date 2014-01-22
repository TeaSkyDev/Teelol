#ifndef _MENU
#define _MENU


#include "Ecran.hh"
#include "Event.hh"
#include <iostream>
#include "Button.hh"

enum Option{
  JOUER, QUITTER
}


class Menu{
public:
  
 

  std::string getText();
  Option getOption();
  
 


private:
  Event m_e;
  //  Text m_text;
  Button m_ok;
  Button m_exit;
  Button m_jouer;

}



#endif
