#include <map>
#include <vector>
#include <pthread.h>
#include <boost/lexical_cast.hpp>

#include "proto.hh"
#include "player.hh"

#include "gr/Character.hh"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

namespace Teelol {

  using namespace netez;
  using namespace std;

  struct session_on_server;
  map<Player*, session_on_server*> players;
  vector<Player*> players_to_delete;

  enum state_t {
    STARTING,
    STARTED
  };

  struct session_on_server: public session<my_proto>{
    state_t state;
    string  nick;
    Player * m_player;
    Form * f;
    session_on_server(socket & io): session(io) {
      state = STARTING;
      f = new Form(10,30,10,300);
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
			x = boost::lexical_cast<int>(x);
			y = boost::lexical_cast<int>(y);
			proto.moveOk(x, y);
		
    	}
    }

    void do_move(string mv) {

      if(mv == "right") {
	m_player->move_right();

      } else if(mv == "left") {
	m_player->move_left();

      } else if(mv == "jump") {
	m_player->jump();

      } else if(mv == "stopx") {
	m_player->stop_x();

      }
      m_player->pass_row();

     
      
      int x = boost::lexical_cast<int>(m_player->get_x());
      int y = boost::lexical_cast<int>(m_player->get_y());
      
      proto.moveOk(x, y);

    	auto it = players.begin();
    	for(it = players.begin(); it != players.end(); it++) {
    		if(it->first != m_player) {
    			it->second->proto.moved(x, y, nick);
    		}
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
			Player *new_player = new Player(_nick, 10, 10, 10, 10, NULL);
			m_player = new_player;
			//temporaire

			players[new_player] = this;
			nick = _nick;
			proto.ok();
			
			cout << _nick << " a changé son pseudo" << endl;

			//Préviens tout le monde que le joueur s'est connecté
			player_joined();
			proto.okNick(_nick);
		} else {
			proto.err("Nick already use !");
		}
		//temporaire
		m_player->add_obstacle(*f);
		int f_x = boost::lexical_cast<int>(f->get_x());
		int f_y = boost::lexical_cast<int>(f->get_y());
		int f_h = boost::lexical_cast<int>(f->get_h());
		int f_l = boost::lexical_cast<int>(f->get_l());
		proto.addObstacle(f_x,f_y,f_h,f_l);
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
			} else {
				pthread_mutex_lock(&mutex);	
				players_to_delete.push_back(it->first);
				pthread_mutex_unlock(&mutex);
			}
		}	
	}

  };
};

void * boucle_suppr(void * arg) {
	while(1) {
		if(Teelol::players_to_delete.size() != 0) {
			pthread_mutex_lock(&mutex);
			auto it = Teelol::players.find(Teelol::players_to_delete[Teelol::players_to_delete.size() - 1]);
			Teelol::players.erase(it);
			Teelol::players_to_delete.pop_back();
			pthread_mutex_unlock(&mutex);
		}
	}
}

int main(int argc, char ** argv){
  
  pthread_t th_boucle_suppr;
  pthread_create(&th_boucle_suppr, NULL, boucle_suppr, (void*)NULL);

  netez::server<Teelol::session_on_server> server(argc,argv);

  server.join();
  pthread_cancel(th_boucle_suppr);

}
				
