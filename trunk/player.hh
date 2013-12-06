#ifndef DEF_PLAYER
#define DEF_PLAYER

/*
	Classe représentant un joueur 
*/

class Player {

	public:
		Player(std::string nick);

		void set_position(unsigned int x, unsigned int y);
		void set_nick(std::string _nick);

		int get_x()const;
		int get_y()const;
		std::string get_nick()const;

	private:
		std::string m_nick;
		int 		m_x;
		int 		m_y;

};

#endif
