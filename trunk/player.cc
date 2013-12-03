#include <iostream>
#include "player.hh"

using namespace std;

Player::Player(string nick) : m_nick(nick), m_x(0), m_y(0) {}

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
void Player::set_nick(string _nick) {
	m_nick = _nick;
}
