#include "netez.hh"
#include <iostream>

/*
  Protocole utilisé par la partie réseaux
*/
namespace Teelol{

  using namespace std;
  using namespace netez;

  struct my_proto: public protocol<>{
    message <0, void(string)>                     move;          //demande au serveur si un la position désirée est ok
    message <1, void(int, int)>                   moveOk;        //le serveur envoie les cooronnées possibles suite à le demande
    message <2, void(int, int, string)>           moved;         //indique aux joueurs la nouvelle position de l'un d'entre eux
    message <3, void(string)>                     nick;          //demande de changemenet/nouveau pseudo
    message <4, void(string)>                     err;           //réponse serveur : erreur
    message <5, void()>                           ok;            //réponse serveur : succès
    message <6, void(string)>                     joined;        //Informe les joueurs d'un arrivant
    message <7, void(string)>                     left;          //Informe les joueurs d'un départ
    message <8, void()>                           quit;          //Signal au serveur de la déconnexion du client
    message <9, void(string)>                     okNick ;       //réponse positive à la demande de pseudo d'un joueur
    message <10, void(string, int,int,int,int)>   addBullet;     //serveur envoi une bullet au client
    message <11, void(int, int , int , int)>      shoot;         //client indique qu'il a tiré
    message <12, void(int, int, int ,int, int)>   addObstacle;   //serveur envoi un obstacle a afficher au client
    message <13, void(int)>                       rotate;        //le client envoi qu'il tourne son arme
    message <14 , void(int, string)>              rotated;       //serveur envoi qu'un client a tourne son arme
    message <15, void(int)>                       nbAmmo;        //serveur envoi le nombre de munition restante au client
    message <16, void(int)>                       hurt;        //serveur envoi au client qu'il s'est fait mal
    message <17, void(string)>                    hurted;      //serveur envoi qu'un client s'est fait mal
    message <18, void(int)>                       health;      //serveur envoi au client qu'il a gagne de la vie
    message <19, void(int, int, int, int)>        addItem;     //serveur envoi au client un item a afficher
    message <20, void(int)>                       hideItem;    //serveur envoi qu'il faut cacher l'item
    message <21 , void(int)>                      showItem;    //serveur envoi qu'il faut afficher l'item
    message <22, void()>                          winPoint;    //serveur envoi au client qu'il a gagner des points
    message <23, void()>                          loosePoint;  //serveur envoi au client qu'il a perdu des points
    message <24, void(string)>                    explode;     //serveur envoi l'explosion d'un bullet
    message <25, void(string)>                    notif;       //serveur envoi une notification à afficher au client

    my_proto(socket &io): protocol<>(io), move(this), moveOk(this),
			  nick(this),     err(this),  ok(this),
			  joined(this),   left(this), moved(this), quit(this), 
			  okNick(this), addObstacle(this), addBullet(this), 
			  shoot(this), rotate(this), rotated(this), nbAmmo(this),
			  hurt(this), hurted(this), health(this), 
			  addItem(this), hideItem(this), showItem(this),
			  winPoint(this), loosePoint(this), explode(this), notif(this)
			  
    {}
    

  };



};
