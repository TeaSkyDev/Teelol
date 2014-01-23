#include "Menu.hh"

using namespace std;



Menu::Menu(Ecran * e){
  m_e = e;
  int x = e->get_h()/2 - 50;
  int y = e->get_l()/2 - 100;
  m_jouer = new Button("Jouer", x,y, 50,100);
  y += 100;
  m_exit = new Button("Quitter", x,y,50,100);
}


void Menu::start(){
  while(!m_jouer->getClicked() && !m_exit->getClicked()){
    m_event.UpdateEvent();
    m_jouer->pass_row(m_event);
    m_exit->pass_row(m_event);
    m_e->clean();
    m_jouer->show(m_e);
    m_exit->show(m_e);
    m_e->Flip();
  }
  if(m_jouer->getClicked())
    m_option = JOUER;
  else 
    m_option = QUITTER;
}


Option Menu::getOption(){
  return m_option;
}
