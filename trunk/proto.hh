#include "netez.hh"
#include <iostream>
namespace Teelol{

  using namespace std;
  using namespace netez;

  struct my_proto: public protocol<>{
    message <0, void(int, int)> move;  //requete client
    message <1, void(int, int)> moveOk;//reponse serveur
    message <2, void(int, int, string)> moved;
    message <3, void(string)>   nick;
    message <4, void(string)>   err;
    message <5, void()>         ok;
    message <6, void(string)>   joined;
    message <7, void(string)>   left;
    message <8, void()>         quit;

    my_proto(socket &io): protocol<>(io), move(this), moveOk(this),
        nick(this),     err(this),  ok(this),
        joined(this),   left(this), moved(this), quit(this)
    {}
    

  };



};
