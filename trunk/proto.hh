#include "netez.hh"
#include <iostream>
namespace Teelol{

  using namespace std;
  using namespace netez;

  struct my_proto: public protocol<>{
    message <0, void(int, int)> move;  //requete client
    message <1, void(int, int)> moveOk;//reponse serveur
    message <2, void(string)>   nick;
    message <3, void(string)>   err;
    message <4, void()>         ok;
    message <5, void(string)>   joined;
    message <6, void(string)>   left;

    my_proto(socket &io): protocol<>(io), move(this), moveOk(this),
			  nick(this),     err(this),  ok(this),
			  joined(this),   left(this)
    {}
    

  };



};
