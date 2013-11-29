#include "proto.hh"

namespace Teelol{
  using namespace netez;
  using namespace std;

  struct session_on_server: public session<my_proto>{};


};


int main(int argc, char ** argv){
  netez::server<Teelol::session_on_server> server(argc,argv);
  server.join();

}
				
