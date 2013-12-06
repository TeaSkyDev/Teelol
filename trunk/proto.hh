#include "netez.hh"
#include <iostream>

/*
  Protocole utilisé par la partie réseaux
*/
namespace Teelol{

  using namespace std;
  using namespace netez;

  struct my_proto: public protocol<>{
    message <0, void(int, int)>         move;          //demande au serveur si un la position désirée est ok
    message <1, void(int, int)>         moveOk;        //le serveur envoie les cooronnées possibles suite à le demande
    message <2, void(int, int, string)> moved;         //indique aux joueurs la nouvelle position de l'un d'entre eux
    message <3, void(string)>           nick;          //demande de changemenet/nouveau pseudo
    message <4, void(string)>           err;           //réponse serveur : erreur
    message <5, void()>                 ok;            //réponse serveur : succès
    message <6, void(string)>           joined;        //Informe les joueurs d'un arrivant
    message <7, void(string)>           left;          //Informe les joueurs d'un départ
    message <8, void()>                 quit;          //Signal au serveur de la déconnexion du client
    message <9, void(string)>           okNick;        //réponse positive à la demande de pseudo d'un joueur

    my_proto(socket &io): protocol<>(io), move(this), moveOk(this),
        nick(this),     err(this),  ok(this),
        joined(this),   left(this), moved(this), quit(this), okNick(this)
    {}
    

  };



};
