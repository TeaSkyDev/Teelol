#include <vector>

#include "proto.hh"
#include "player.hh"
#include "gr/Event.hh"
#include "gr/Ecran.hh"

namespace Teelol {

  using namespace std;
  using namespace netez;
  
  enum state_t {
      STARTING,
      STARTED
  };

  struct session_on_client: public session<my_proto>{
  
    vector<Player*> players;
    Player * player;

    state_t state;

    session_on_client(socket &io): session<my_proto>(io){

      player = new Player("nameless", 0, 0, 0, 0, NULL);
      state  = STARTING;

      proto.moveOk.sig_recv.connect(EZMETHOD(this, do_moveOk));
      proto.moved.sig_recv.connect(EZMETHOD(this, do_moved));
      proto.err.sig_recv.connect(EZMETHOD(this, do_err));
      proto.ok.sig_recv.connect(EZMETHOD(this, do_ok));
      proto.joined.sig_recv.connect(EZMETHOD(this, do_joined));
      proto.left.sig_recv.connect(EZMETHOD(this, do_left));
      proto.okNick.sig_recv.connect(EZMETHOD(this, do_okNick));

      sig_begin.connect(EZMETHOD(this,on_begin));
      sig_end.connect(EZMETHOD(this, on_end));
    }

    void on_begin() {
      string n;
      cout << "nick : ";
      cin >> n;

      proto.nick(n);

    }

    void on_end() {
      proto.quit();
    }
    
    void do_moveOk(int x ,int y){
      player->set_position(x, y);
    }

    void do_moved(int x, int y, string nick) {
      for(int i = 0; i < players.size(); i++) {
        if(players[i]->get_nick() == nick) {
          players[i]->set_position(x, y);
          break;
        }
      } 
    }

    void do_err(string err) {
      cout << "System : " << err << endl;
    }

    void do_okNick(string n) {
      if(state == STARTING) {

        state = STARTED;
      }
      player->set_nick(n);
      cout << "System : nick changed !" << endl;
    }

    void do_ok() {
      cout << "System : success" << endl;
    }

    void do_joined(string nick) {
      players.push_back(new Player(nick, 0, 0, 0, 0, NULL));
    }

    void do_left(string nick) {
      for(int i = 0; i < players.size(); i++) {
        if(players[i]->get_nick() == nick) {
          delete players[i];
          players[i] = players[players.size() - 1];
          players.pop_back();
          break;
        }
      }
    }
    
  };
};




void * routine(void * arg){
  Ecran sc(400,400);
  Event e;
  Teelol::session_on_client * c = (Teelol::session_on_client*)arg;
  while(!e[QUIT]){
    e.UpdateEvent();
    if(e[LEFT])
      c->proto.move("left");
    else if(e[RIGHT])
      c->proto.move("right");
    else c->proto.move("stop_x");
    if(e[JUMP]) c->proto.move("jump");
  }
}


int main(int argc, char ** argv){
  netez::client<Teelol::session_on_client> client(argc,argv);
  pthread_t th;
  pthread_create(&th, NULL, routine, (void*)&client.session);
  pthread_join(th,NULL);
  client.join();
  
  
}
