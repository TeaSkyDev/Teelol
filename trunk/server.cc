#include <map>
#include <vector>
#include <pthread.h>
#include <boost/lexical_cast.hpp>

#include "proto.hh"
#include "player.hh"

#include "gr/Character.hh"
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

  void load_Map(string name){
    ifstream fichier(name.c_str());
    int type,x,y,h,l, img,type2;

    fichier >> screen_s.l >> screen_s.h >> NbAmmo;
    cout << "l = " << screen_s.l << ", h =" << screen_s.h << endl;

    while(!fichier.eof()){
      fichier >> type >> x >> y >> h >> l >> img;
      switch(type){
      case 1:
	obstacle.push_back(Form(x,y,h,l));
	obstacle[obstacle.size()-1].set_image((Image_t)img);
	break;
      case 2:
	fichier >> type2;
	tab_item.push_back(Item(x,y,h,l,(ITEM_T)type2));
	tab_item[tab_item.size()-1].set_image((Image_t)img);
	break;		   
      }
    }
    fichier.close();
  }


  struct session_on_server: public session<my_proto>{
    state_t state;
    string  nick;
    Player * m_player;
    Form * f;
    int last_ammo_size, last_life_size;
    session_on_server(socket & io): session(io) {
      state = STARTING;
      last_ammo_size = last_life_size = 10;
      f = new Form(10,300,10,300);
      proto.move.sig_recv.connect(EZMETHOD(this, do_move));
      proto.nick.sig_recv.connect(EZMETHOD(this, do_nick));
      proto.quit.sig_recv.connect(EZMETHOD(this, do_quit));
      proto.rotate.sig_recv.connect(EZMETHOD(this, do_rotate));
      proto.shoot.sig_recv.connect(EZMETHOD(this, do_shoot));
      sig_begin.connect(EZMETHOD(this,on_begin));
    }
  	

    void on_begin() {
      
      int y = -10;
      int x = rand()%screen_s.l;
      cout << "rand = " << x << ", screen_s.l = " << screen_s.l << endl;

      proto.moveOk(x, y);
      
    }

    void die(){
      int o_x = rand()%screen_s.l;
      m_player->spawn(o_x,-10);
      proto.nbAmmo(10);
      proto.health(10);
    }


    void verif_repop(){
      int x = m_player->get_x();
      int y = m_player->get_y();
      int l = m_player->get_l();
      if(y > screen_s.h)
	m_player->set_y(-10);
      if(x > screen_s.l)
	m_player->set_x(0);
      if(x + l< 0)
	m_player->set_x(screen_s.l - l);
    }


    void do_move(string mv) {
      {
	ezlock hold(ez_mutex);
	
	if(mv == "right") {
	  m_player->move_right();
	  
	} else if(mv == "left") {
	  m_player->move_left();
	  
	} else if(mv == "jump") {
	  m_player->jump();
	  
	} else if(mv == "stopx") {
	  m_player->stop_x();
	  
	}
	last_life_size = m_player->get_life();
	m_player->pass_row();  
	verif_repop();
	if(m_player->get_life() <= 0)
	  die();
	int x = m_player->get_x();
	int y = m_player->get_y();
	int dmg = m_player->get_hurt();

	proto.moveOk(x, y);
	
	proto.hurt(dmg);
	if(last_ammo_size != m_player->get_ammo()->get_NbAmmo()){
	  int nb = m_player->get_ammo()->get_NbAmmo();
	  proto.nbAmmo(nb);
	}
	if(last_life_size != m_player->get_life() && last_life_size < m_player->get_life()){
	  int _health = m_player->get_life() - last_life_size;
	  proto.health(_health);
	}
	
        for(int i = 0 ; i < tab_item.size() ; i++){
	  if(tab_item[i].hidden()){
	    proto.hideItem(i);
	  }
	  else proto.showItem(i);
	}
	auto it = players.begin();
	for(; it != players.end(); it++) {
	  if(it->first != m_player) {
        
	  it->second->proto.moved(x, y, nick);
	  if(dmg > 0)
	    it->second->proto.hurted(nick);
	}
      }
      for(it = players.begin(); it != players.end() ; it++){
	for(int i = 0 ; i < m_player->get_ammo()->get_max() ; i++){
	  int x = (*m_player->get_ammo())[i]->get_x();
	  int y = (*m_player->get_ammo())[i]->get_y();
	  it->second->proto.showMissile(x,y);
	}
	for(int i = 0 ; i < m_player->get_ammo()->get_explode_size() ; i++){
	  int x = m_player->get_ammo()->get_exploded(i)->get_x();
	  int y = m_player->get_ammo()->get_exploded(i)->get_y();

	  it->second->proto.showExplosion(x,y);

	  if(m_player->get_ammo()->get_exploded(i)->get_killed() != NULL) {
	    Character* player_killed = (Character*)(m_player->get_ammo()->get_exploded(i)->get_killed());
	    m_player->get_ammo()->get_exploded(i)->set_killed(NULL);
	    if(player_killed->get_life() == 0) {
	      if(player_killed == m_player) {
		m_player->loose_point();
		proto.loosePoint();
	      } else {
		m_player->win_point();
		proto.winPoint();
	      }
	    }
	  }
	}
      }
      }
      
    }
   
    


    void do_nick(string _nick) {
      bool nick_ok = true;
      auto it = players.begin();
	
      for(; it != players.end(); it++) {
	if(it->first->get_nick() == _nick) {
	  nick_ok = false;
	}
      }
	
      if(nick_ok) {
	cout<<"nick accepte"<<endl;
	m_player  = new Player(_nick, I_TEE_P,rand()%screen_s.l , -10, 50, 50, NULL);

	nick = _nick;
	proto.ok();
	cout << _nick << " a changé son pseudo" << endl;
	player_joined();

	init_NewPlayer(_nick);
	players[m_player] = this;
	cout<<"signaux envoyer"<<endl;
      }
      else {
	proto.err("Nick already use !");
      }
    }

    void init_NewPlayer(string _nick){
      
      proto.okNick(_nick);

      for(auto it = obstacle.begin() ; it != obstacle.end() ; it++){
	*m_player << *it;
	send_Form(it);
      }
      for(auto it = players.begin(); it != players.end(); it++) {
	m_player->add_obstacle(it->first);
      }
      for(int i = 0 ; i < tab_item.size() ; i++){
	*m_player << tab_item[i];
	send_Item(&tab_item[i],i);
      }
      
      int nb = m_player->get_ammo()->get_NbAmmo();
      m_player->get_ammo()->set_dmg(NbAmmo);
      proto.nbAmmo(nb);
    }
    
    void send_Form(vector<Form>::iterator it){
      int x = it->get_x();
      int y = it->get_y();
      int h = it->get_h();
      int l = it->get_l();
      
      int img = (int)it->get_img();
      proto.addObstacle(img,x,y,h,l);
    }

    void send_Item(Item *it, int i){
      int x = it->get_x();
      int y = it->get_y();
      int img = (int)it->get_img();
      proto.addItem(x,y,img,i);
    }
    
    void player_joined() {
      auto it = players.begin();
      cout<<"avant player_joined"<<endl;
      for(it = players.begin(); it != players.end(); it++) {
	if(it->first->get_nick() != nick) {
	  it->second->proto.joined(nick);
	  proto.joined(it->first->get_nick());
	  it->first->add_obstacle(m_player);
	}
      }
			  
    }

    void do_rotate(int angle){
	auto it = players.begin();
	for(; it != players.end(); it++) {
	  if(it->first != m_player) {  
	    it->second->proto.rotated( angle, nick);
	  }
	}
			      
    }


    void do_shoot(int x1, int y1,int x2, int y2 ){
      m_player->get_ammo()->shoot(x1,x2,y1,y2);
      int nb = m_player->get_ammo()->get_NbAmmo();
      last_ammo_size = m_player->get_ammo()->get_NbAmmo();
      proto.nbAmmo(nb);
    }

    void do_quit() {
      auto it = players.begin();
      for(it = players.begin(); it != players.end(); it++) {
	if(it->first->get_nick() != nick) {
	  it->second->proto.left(nick);
	} else {
	  pthread_mutex_lock(&mutex);	
	  players_to_delete.push_back(it->first);
	  pthread_mutex_unlock(&mutex);
	}
      }	
    }
    
  };
};

void * boucle_suppr(void * arg) {
  while(1) {
    if(Teelol::players_to_delete.size() != 0) {
      pthread_mutex_lock(&mutex);
      auto it = Teelol::players.find(Teelol::players_to_delete[Teelol::players_to_delete.size() - 1]);
      Teelol::players.erase(it);
      Teelol::players_to_delete.pop_back();

      /* Pour chaque player, on supprime la collision avec le player supprimé */
      auto itp = Teelol::players.begin();
      for(; itp != Teelol::players.end(); itp++) {
	itp->first->delete_obstacle(it->first);
      }

      pthread_mutex_unlock(&mutex);
    }
  }
}

int main(int argc, char ** argv){
  
  srand(time(NULL));

  pthread_t th_boucle_suppr;
  pthread_create(&th_boucle_suppr, NULL, boucle_suppr, (void*)NULL);
  if(argc > 1){
    if(argc == 2){
      Teelol::load_Map(argv[1]);
    }
    else if(argc == 4){
      Teelol::load_Map(argv[3]);
    }
    else 
      Teelol::load_Map("../const/map.lvl");
  }
  else 
    Teelol::load_Map("../const/map.lvl");
  netez::server<Teelol::session_on_server> server(argc,argv);

  server.join();
  pthread_cancel(th_boucle_suppr);

}
				
