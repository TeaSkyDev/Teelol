#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "netez.hh"

class Player {

	public:
		Player(std::string nick);

		void set_position(unsigned int x, unsigned int y);

		int get_x();
		int get_y();
		std::string get_nick();


};

#endif