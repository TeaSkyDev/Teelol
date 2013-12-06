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
      proto.quit.sig_recv.connect(EZMETHOD(this, do_quit));

      sig_begin.connect(EZMETHOD(this,on_begin));
    }
  	

    void on_begin() {
    	int x = 0;
    	int y = 0;

    	//Si il y a au moins un joueur, on incrémente les coord jusqu'à avoir quelque chose de cool
    	if(players.size() != 0) {
			bool ok = false;
			while(!ok) {
				ok = true;
				auto it = players.begin();

				for(it = players.begin(); it != players.end(); it++) {
					if(it->first->get_x() == x && it->first->get_y() == y) {
						ok = false;
					}
				}

				if(!ok) {
					x++;
					y++;
				}
			}
			proto.moveOk(x, y);
    	}
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

    void do_nick(string _nick) {
    	bool nick_ok = true;
    	auto it = players.begin();

      	for(it = players.begin(); it != players.end(); it++) {
			if(it->first->get_nick() == _nick) {
	  			nick_ok = false;
	  		}
		}

		if(nick_ok) {
			Player *new_player = new Player(_nick);
			players[new_player] = this;
			nick = _nick;
			proto.ok();
			
			//Préviens tout le monde que le joueur s'est connecté
			player_joined();
			proto.okNick(_nick);
		} else {
			proto.err("Nick already use !");
		}
    }
	
	void player_joined() {
		auto it = players.begin();
		
		for(it = players.begin(); it != players.end(); it++) {
			if(it->first->get_nick() != nick) {
				it->second->proto.joined(nick);
			}
		}
	}

	void do_quit() {
		auto it = players.begin();
		
		for(it = players.begin(); it != players.end(); it++) {
			if(it->first->get_nick() != nick) {
				it->second->proto.left(nick);
			}
		}	
	}

  };
};

	

int main(int argc, char ** argv){
  netez::server<Teelol::session_on_server> server(argc,argv);
  server.join();

}
				
