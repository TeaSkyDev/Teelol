#include <iostream>

#include "player.hh"

#include "gr/Character.hh"
#include "gr/Ecran.hh"

using namespace std;

Player::Player(string nick, int x, int y, int h, int l, Ecran * ecran) : m_nick(nick), Character(img, x, y , h , l , screen) {}

void Player::set_nick(string _nick) {
	m_nick = _nick;
}
