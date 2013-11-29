#include "proto.hh"


namespace Teelol{

  using namespace std;
  using namespace netez;
  
  
  
  struct session_on_client: public session<my_proto>{
    
    session_on_client(socket &io): session<my_proto>(io){
      proto.moveOk.sig_recv.connect(EZMETHOD(this, do_moveOk));
    }
    
    void do_moveOk(int a ,int b){
    }
    
  };
};


int main(int argc, char ** argv){
  netez::client<Teelol::session_on_client> client(argc,argv);
  client.join();
  
}
