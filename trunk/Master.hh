#ifndef _MASTER
#define _MASTER

#include <iostream>
#include <map>
#include <vector>
#include "server.hh"
#include "Map.hh"
#include "gr/Event.hh"
#include "gr/Item.hh"
#include "player.hh"

namespace Teelol {
    class Master {
    
    public:

	Master(int, char **);
    
	void pass_row();
	bool launch_server();
	void boucle_Inter(int, char**);
	void new_session(session_on_server&, Player&);
	
	~Master();
    
	//session slots
    
	void session_connect( std::string nick, Player * p);
	void session_move   ( std::string dir, Player * p );
	void session_shoot  ( int , int , int , int , Player *);
	void session_quit   ( Player * );

	//player slots
    
	void player_hurt ( int );
	void player_die  ();
	void player_kill (std::string);
	void player_break(std::string);
	void player_move (int, int);


	//signals
	signal<void()> nick_accept;
	signal<void()> nick_refused;


    private:
	
	std::map<Player *, std::string > nick_map;
	std::map<Player *, session_on_server*> first_team;
	std::map<Player *, session_on_server*> second_team;
	Map map_server;
	std::vector <Item> tab_item;
	netez::server <Teelol::session_on_server> * server;
	bool m_quit;
    };
};


#endif
