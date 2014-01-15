#include <map>
#include <vector>
#include <pthread.h>

#include "proto.hh"
#include "player.hh"

#include "gr/Item.hh"


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

namespace Teelol {

  using namespace netez;
  using namespace std;

  struct screen_size {
    int l;
    int h;
  };

  ezmutex ez_mutex;
  struct session_on_server;
  map<Player*, session_on_server*> players;
  vector<Form> obstacle;
  vector<Item>  tab_item;
  vector<Player*> players_to_delete;
  screen_size screen_s;
  int NbAmmo;
  
  enum state_t {
    STARTING,
    STARTED
  };

 
  struct session_on_server: public session<my_proto>{
    state_t state;
    string  nick;
    Player * m_player;
    Form * f;
    int cur_id;
    int last_ammo_size, last_life_size;

    session_on_server(socket & io);  	


    //lorsque le player meurt on le respawn ailleur avec toute sa vie et toute ses munitions
    void die();
    
    //si le player sort de l'ecran on le repop de l'autre cote
    void verif_repop();

    //verifie si le player a pris un item qui donne de la vie
    void verif_lifeAndAmmo();

    //verifie si le joueur a gagner des points
    void verif_Points(int i);

    //envoi tout les mouvement perte de vie... aux autres joueur de m_player
    void send_all_to_other(int x, int y, int dmg);

    //sur la reception d'un event du client
    void do_move(string mv);   
    
    //au debut lorsque le player demande un nom
    void do_nick(string _nick);

    //initialise le player avec le nom et une position aleatoire
    //ajoute tout les obstacles necessaire
    void init_NewPlayer(string _nick);

    //envoi une forme au client
    void send_Form(vector<Form>::iterator it);

    //envoi un item au client
    void send_Item(Item *it, int i);

    //envoi a tout les joueur l'arrive d'un nouveau joueur
    void player_joined() ;

    //suite a la reception de l'info sur la rotation de l'arme d'un client
    void do_rotate(int angle);

    void send_other_new_bullet(int x_s, int y_s);

    //suive a l'event de tir du client
    void do_shoot(int x1, int y1,int x2, int y2 );

    //un client envoi qu'il quitte 
    void do_quit();
  };
};
