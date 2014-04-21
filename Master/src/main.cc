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
      proto.ping.sig_recv.connect(EZMETHOD(this, do_ping));
    }
  

    void set_master(Master<session_> * m) {
    }

    void do_ping() {
      cout << "PING" << endl;
      ping_recv(this);
    }
  

    void ping_recv_slot() {
      proto.pong();
    }
  
    signal<void(session_ *)> ping_recv;

  };

};
int main(int argc, char ** argv) {
  Teelol::Master<Teelol::session_> ma(argc, argv);
  ma.join();
}
