#include <map>

#include "proto.hh"
#include "player.hh"

namespace Teelol{
  using namespace netez;
  using namespace std;

  struct session_on_server;
  map<Player*, session_on_server*> players;

  enum state_t {
    STARTING,
    STARTED
  };

  struct session_on_server: public session<my_proto>{
    state_t state;
    string  nick;

    session_on_server(socket & io): session(io) {
      state = STARTING;

      proto.move.sig_recv.connect(EZMETHOD(this, do_move));
      proto.nick.sig_recv.connect(EZMETHOD(this, do_nick));
    }
  	

    void do_move(int x, int y) {

      bool move_ok = true;

      auto it = players.begin();

      for(it = players.begin(); it != players.end(); it++) {
	if(it->first->get_nick() != nick) {
	  if(it->first->get_x() == x && it->first->get_y() == y) {
	    move_ok = false;
	  }
	}
      }

      if(move_ok) {
	proto.moveOk(x, y);

	for(it = players.begin(); it != players.end(); it++) {
	  if(it->first->get_nick() != nick) {
	    it->second->proto.moved(x, y, nick);
	  } else {
	    it->first->set_position(x, y);
	  }
	}
      } else {
	  proto.err("Mauvaises cooordonnées.");
	}

    }

    void do_nick(string n) {
    	bool nick_ok = true;
    	auto it = players.begin();

      	for(it = players.begin(); it != players.end(); it++) {
			if(it->first->get_nick() == nick) {
	  			nick_ok = false;
	  		}
		}

		if(nick_ok) {
			proto.ok();
		} else {
			proto.err("erreur nick");
		}
    }

  };
};


int main(int argc, char ** argv){
  netez::server<Teelol::session_on_server> server(argc,argv);
  server.join();

}
				
