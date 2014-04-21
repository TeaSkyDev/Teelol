#include "../include/proto.hh"
#include <iostream>

using namespace std;

namespace Teelol {
  struct session_ : public session<m_proto> {
    
    session_(socket & io) : session<m_proto>(io) {
      proto.pong.sig_recv.connect(EZMETHOD(this, do_pong));
      sig_begin.connect(EZMETHOD(this, on_begin));

    }

    void on_begin() {
      proto.ping();
    }


    void do_pong() {
      cout << "PONG" << endl;
    }
    

  };
};


int main(int argc, char ** argv) {
  netez::client<Teelol::session_> client(argc, argv);
  client.join();
}
