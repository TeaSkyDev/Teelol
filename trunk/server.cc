#include <vector>

#include "proto.hh"
#include "player.hh"

namespace Teelol{
  	using namespace netez;
  	using namespace std;

  	vector<Player> players;

  	enum state_t {
  		STARTING,
  		STARTED
  	};

  	struct session_on_server: public session<my_proto>{
  		state_t state = STARTING;
  		string  nick;

  		proto.send.sig_recv.connect(EZMETHOD(this, do_move));
  		proto.send.sig_recv.connect(EZMETHOD(this, do_nick));
  	};

  	void do_move(int x, int y) {

  		bool move_ok = true;

  		for(int i = 0; i < players.size(); i++) {
  			if(players[i].get_nick() != nick) {
  				if(players[i].get_x() == x && players[i].get_y() == y) {
  					move_ok = false;
  				}
  			}
  		}

  		if(move_ok) {
  			proto.moveOk(x, y);

  			for(int i = 0; i < players.size(); i++) {
	  			if(players[i].get_nick() != nick) {
	  				players[i].session->proto.moved(x, y, nick);
	  			}
  			}
  		} else {
  			proto.err("Mauvaises cooordonnées.");
  		}

  	}

};


int main(int argc, char ** argv){
  netez::server<Teelol::session_on_server> server(argc,argv);
  server.join();

}
				
