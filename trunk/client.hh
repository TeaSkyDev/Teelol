#include <vector>

#include "proto.hh"
#include "player.hh"
#include "gr/Event.hh"
#include "gr/Ecran.hh"
#include "gr/Item.hh"
#include "gr/Parse.hh"
#include "gr/Notif.hh"
#include "gr/Interface/Focuser.hh"
#include "gr/Interface/NumberEdit.hh"
#include "gr/Interface/Button.hh"
#include "Map.hh"

bool tentative_connexion = true;

namespace Teelol {

    using namespace std;
    using namespace netez;
  
    enum state_t {
	STARTING,
	STARTED,
	QUIT
    };


    screen_size screen_s;    

    struct session_on_client: public session<my_proto>{
	ezmutex mutex;
	vector<Player*> players;
	vector<Form> obstacle;
	map<string,Bullet*> map_bullet;
	vector<Bullet> vec_explode;
	map<int, Item*> map_item;
	Player * player;
	Ecran  *sc;
	Notif  *notif;
	state_t state;    
	Parse p;
	point mid_screen;

	session_on_client(socket &io);

	void on_end();
    
	//le serveur envoi que le joueur est en x,y
	void do_moveOk(int x ,int y);

	//le joueur nick est en x,y
	void do_moved(int x, int y, string nick);
    
	//erreur envoyer du serveur
	void do_err(string err);
    
	//le nick est accepte
	void do_okNick(string n);
    
	//reponse positive du serveur
	void do_ok();

	//un nouveau joueur est present
	void do_joined(string nick);

	//le joueur nick est partis
	void do_left(string nick);

	//reception d'un obstacle depuis le serveur
	void do_addObstacle(int img, int x, int y, int h, int l);
    
	//le joueur nick a tourner son arme de l'angle angle
	void do_rotated(int angle, string nick);
    
	//un missile est tiré en x,y
	void do_addBullet(string s, int x, int y, int x_s, int y_s);

	//un missile a explosé
	void do_explode(string s);

	//le client a nb munitions
	void do_nbAmmo(int nb);

	//le joueur a pris dmg degat
	void do_hurt(int dmg);

	//le joueur _nick a pris des degat
	void do_hurted(string _nick);

	//le client a recuperer h vie
	void do_health(int h);

	//ajout d'un Item sur la map
	void do_addItem(int x, int y, int img, int id);


	//l'Item d'id i doit etre cache
	void do_hideItem(int i);
    
	//l'item d'id i doit etre afficher
	void do_showItem(int i);

	//le joueur gagne 1 points
	void do_winPoint();

	//le joueur perd 1 points
	void do_loosePoint();

	//affiche la notification envoyée par le serveur
	void do_notif(string msg);

	//affiche les autres joueur avec leurs nom sur la tete
	void show_players();

	//affiche le joueur
	void show_m_player();

	//boucle d'affichage
	void affiche();
    
	//fait tourner l'arme du joueur
	//envoi au serveur que l'arme a été tourne
	void rotationArme(int _x, int _y);

	//envoi que le client a tire depuis les point envoyer
	void shoot();

	void map_Bullet_pass_row();

    };
};
