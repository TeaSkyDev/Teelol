#include <iostream>
#include "player.hh"

using namespace std;

Player::Player() : m_nick(nick) {}

int Player::get_x() {
	return m_x;
}
int Player::get_y() {
	return m_y;
}
string Player::get_nick() {
	return m_nick;
}

void Player::set_position(unsigned int x, unsigned int y) {
	m_x = x;
	m_y = y;
}