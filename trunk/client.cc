#include <vector>

#include "proto.hh"
#include "player.hh"

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

      player = new Player("nameless");
      state  = STARTING;

      proto.moveOk.sig_recv.connect(EZMETHOD(this, do_moveOk));
      proto.moved.sig_recv.connect(EZMETHOD(this, do_moved));
      proto.err.sig_recv.connect(EZMETHOD(this, do_err));
      proto.ok.sig_recv.connect(EZMETHOD(this, do_ok));
      proto.joined.sig_recv.connect(EZMETHOD(this, do_joined));
      proto.left.sig_recv.connect(EZMETHOD(this, do_left));
      proto.okNick.sig_recv.connect(EZMETHOD(this, do_okNick));

      sig_begin.connect(EZMETHOD(this,on_begin));
    }

    void on_begin() {
      string n;
      cout << "nick : ";
      cin >> n;

      proto.nick(n);

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
      players.push_back(new Player(nick));
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

int main(int argc, char ** argv){
  netez::client<Teelol::session_on_client> client(argc,argv);
  client.join();
  
}
