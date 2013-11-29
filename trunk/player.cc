#include <iostream>
#include "player.hh"

using namespace std;

Player::Player(string nick) : m_nick(nick) {}

int Player::get_x() const{
	return m_x;
}
int Player::get_y() const{
	return m_y;
}
string Player::get_nick() const {
	return m_nick;
}

void Player::set_position(unsigned int x, unsigned int y) {
	m_x = x;
	m_y = y;
}
