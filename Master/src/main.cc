#include "../include/Master.hh"
#include "../include/proto.hh"
#include <iostream>
#include <boost/signals2.hpp>

using boost::signals2::signal;
using namespace std;


namespace Teelol {
  using namespace netez;
  
  struct session_ : public session<m_proto> {

  public :
  
    session_(socket &io) : session<m_proto>(io) {
      proto.nick.sig_recv.connect(EZMETHOD(this, do_nick));
    }
    
    void do_nick( string nick ) {
      master_nick(nick, this);
    }
    

    void error(string msg) {
      proto.err(msg);
    }

    void success() {
      proto.ok();
    }

    signal<void(string, session_ *)> master_nick;

  };

};
int main(int argc, char ** argv) {
  Teelol::Master<Teelol::session_> ma(argc, argv);
  ma.join();
}
