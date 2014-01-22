#include "Notif.hh"

Notif::Notif( Ecran * ec ) {
  TTF_Init();
  m_ecran = ec;
  m_rows_init = 40;
  m_rect.x = ec->get_l()/2;
  m_rect.y = ec->get_h()/2;
  m_police = TTF_OpenFont("../const/Freshman.ttf", 40);
  m_color  = {255, 0, 0};
}

void Notif::pass_row() {
  if(m_rows > 0) {
    m_rows--;
    m_ecran->put(m_surf, m_rect);
  } 
}

void Notif::add_notif(const char * str) {
  m_surf = TTF_RenderText_Blended(m_police, str, m_color);
  m_rows = m_rows_init;
}



