#include "../include/proto.hh"
#include <iostream>

using namespace std;

namespace Teelol {
  struct session_ : public session<m_proto> {
    
    session_(socket & io) : session<m_proto>(io) {

    }
  };
};


int main(int argc, char ** argv) {
  netez::client<Teelol::session_> client(argc, argv);
  client.join();
}
