#include <iostream>

#include "player.hh"

#include "gr/Character.hh"
#include "gr/Ecran.hh"

using namespace std;

Player::Player(string nick, Image_t img, int x, int y, int h, int l, Ecran * screen) : m_nick(nick), Character(img, x, y , h , l , screen) {}

void Player::set_nick(string _nick) {
	m_nick = _nick;
}

string Player::get_nick() const {
	return m_nick;
}

void Player::show_nick(){
  TTF_Init();
  SDL_Color couleur = {255,255,255};
  SDL_Surface * Name = TTF_RenderText_Blended(TTF_OpenFont("../const/Font.ttf",15),m_nick.c_str(), couleur);
  SDL_Rect rect;
  rect.x = m_x - Name->w/2;
  rect.y = m_y - Name->h - Name->h/2;
  m_e->put(Name, rect);
}
