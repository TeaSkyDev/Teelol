#include "server.hh"




namespace Teelol{

 
  session_on_server::session_on_server(socket & io): session(io) {
    cur_id = 0;
    state = STARTING;
    last_ammo_size = last_life_size = 10;
    f = new Form(10,300,10,300);
    proto.move.sig_recv.connect(EZMETHOD(this, do_move));
    proto.nick.sig_recv.connect(EZMETHOD(this, do_nick));
    proto.quit.sig_recv.connect(EZMETHOD(this, do_quit));
    proto.rotate.sig_recv.connect(EZMETHOD(this, do_rotate));
    proto.shoot.sig_recv.connect(EZMETHOD(this, do_shoot));
   
  }
  	

 
  //lorsque le player meurt on le respawn ailleur avec toute sa vie et toute ses munitions
  void session_on_server::die(){
    cout<<"["<<nick<<"] die"<<endl;
    int o_x = rand()%map_server.get_Screen_Size().l;
    m_player->spawn(o_x,-10);
    proto.nbAmmo(10);
    proto.health(10);
  }
    
  //si le player sort de l'ecran on le repop de l'autre cote
  void session_on_server::verif_repop(){
    int x = m_player->get_x();
    int y = m_player->get_y();
    int l = m_player->get_l();
    if(y > map_server.get_Screen_Size().h + 200) {
	die();
	cout<<"["<<nick<<"] suicide"<<endl;
	m_player->loose_point();
	proto.notif("Suicide !");
	send_notif_suicide();
	proto.loosePoint();
    }
  }

  //verifie si le player a pris un item qui donne de la vie
  void session_on_server::verif_lifeAndAmmo(){
    if(last_ammo_size != m_player->get_ammo()->get_NbAmmo())
      {
	cout<<"["<<nick<<"] take ammo"<<endl;
	int nb = m_player->get_ammo()->get_NbAmmo();
	last_ammo_size = m_player->get_ammo()->get_NbAmmo();
	proto.nbAmmo(nb);
      }
    if(last_life_size != m_player->get_life() && last_life_size < m_player->get_life())
      {
	cout<<"["<<nick<<"] take life"<<endl;
	int _health = m_player->get_life() - last_life_size;
	last_life_size = m_player->get_life();
	proto.health(_health);
      }
  }
  
  //verifie si le joueur a gagner des points
  void session_on_server::verif_Points(int i){
    if(m_player->get_ammo()->get_exploded(i)->get_killed() != NULL) 
      {
	Character* player_killed = (Character*)(m_player->get_ammo()->get_exploded(i)->get_killed());
	m_player->get_ammo()->get_exploded(i)->set_killed(NULL);
	if(player_killed->get_life() == 0)
	  {
	    if(player_killed == m_player) {
	      cout<<"["<<nick<<"] suicide"<<endl;
	      m_player->loose_point();
	      proto.notif("Suicide !");
	      send_notif_suicide();
	      proto.loosePoint();
	    } else {
	      cout<<"["<<nick<<"] kill"<<endl;
	      m_player->win_point();
	      Player * p_killed = (Player*)(player_killed);
	      string ntf = "Vous avez tué " + p_killed->get_nick() + " !";
	      proto.notif(ntf.c_str());
	      send_notif_death(p_killed->get_nick());
	      proto.winPoint();
	    }
	  }
      }    
  }
  
  void session_on_server::send_notif_suicide() {
    string msg = m_player->get_nick() + " s'est suicidé !";
    for(auto it : players) {
      if(it.first != m_player) {
	it.second->proto.notif(msg.c_str());
      }
    }
  }

  void session_on_server::send_notif_death(string nick_killed) {
    string msg  = m_player->get_nick() + " a tué " + nick_killed;
    string msg2 = m_player->get_nick() + " vous a tué !";
    for(auto it :players) {
      if(it.first->get_nick() == nick_killed) {
	it.second->proto.notif(msg2);
      } else {
	it.second->proto.notif(msg);
      }
    }
  }

  //envoi tout les mouvement perte de vie... aux autres joueur de m_player
  void session_on_server::send_all_to_other(int x, int y, int dmg){
    for(auto it: players) {
      if(it.first != m_player) {        
	it.second->proto.moved(x, y, nick);
	if(dmg > 0)
	  it.second->proto.hurted(nick);
      }
      for(int i = 0 ; i < m_player->get_ammo()->get_explode_size() ; i++) {
	int id =m_player->get_ammo()->get_exploded(i)->get_id();
	stringstream ident(nick);
	ident << id;
	it.second->proto.explode(ident.str());
	verif_Points(i);
      }  
    }
  }
  
  //sur la reception d'un event du client
  void session_on_server::do_move(string mv) {
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
    m_player->pass_row();  

    verif_repop();
    verif_lifeAndAmmo();
    int dmg = m_player->get_hurt();
    if(dmg > 0){
      proto.hurt(map_server.get_Nb_Ammo());
      last_life_size = m_player->get_life();
    }
    int x = m_player->get_x();
    int y = m_player->get_y();
    proto.moveOk(x, y);
    send_all_to_other(x,y,dmg);
    if(m_player->get_life() <= 0)
      die();
  }
   
    
  //au debut lorsque le player demande un nom
  void session_on_server::do_nick(string _nick) {
    bool nick_ok = true;
    for(auto it: players){	
      if(it.first->get_nick() == _nick) {
	nick_ok = false;
      }
    }
	
    if(nick_ok) {
      cout<<"nick accepte"<<endl;
      m_player  = new Player(_nick, I_TEE_P,rand()%map_server.get_Screen_Size().l , -10, 50, 50, NULL);

      nick = _nick;
      proto.ok();
      cout << _nick << " a changé son pseudo" << endl;
      player_joined();

      init_NewPlayer(_nick);
      players[m_player] = this;

    }
    else {
      proto.err("Nick already use !");
    }
  }

  void session_on_server::send_Form(Form &f){
    int x = f.get_x();
    int y = f.get_y();
    int h = f.get_h();
    int l = f.get_l();
    int img = (int)f.get_img();
    proto.addObstacle(img,x,y,h,l);
  }

  //initialise le player avec le nom et une position aleatoire
  //ajoute tout les obstacles necessaire
  void session_on_server::init_NewPlayer(string _nick){
      
    proto.okNick(_nick);

    for(Form &f: map_server.get_Object_vec()){
      m_player->add_obstacle(&f);
      send_Form(f);
    }
    
    for(auto &it: players){
      m_player->add_obstacle(it.first);
    }
    
    for(int i = 0 ; i < map_server.get_Item_vec().size() ; i++){
      map_server.get_Item(i).add_obstacle(*m_player);
      send_Item(&map_server.get_Item(i),i);
    }
   
    
    int nb = m_player->get_ammo()->get_NbAmmo();
    m_player->get_ammo()->set_dmg(map_server.get_Nb_Ammo());
    proto.nbAmmo(nb);
  }
    
  //envoi une forme au client
  void session_on_server::send_Form(vector<Form>::iterator it){
    int x = it->get_x();
    int y = it->get_y();
    int h = it->get_h();
    int l = it->get_l();
    int img = (int)it->get_img();
    proto.addObstacle(img,x,y,h,l);
  }

  //envoi un item au client
  void session_on_server::send_Item(Item *it, int i){
    int x = it->get_x();
    int y = it->get_y();
    int img = (int)it->get_img();
    proto.addItem(x,y,img,i);
  }
    
  //envoi a tout les joueur l'arrive d'un nouveau joueur
  void session_on_server::player_joined() {
    for (auto &it : players) {
      if(it.first->get_nick() != nick) {
	it.second->proto.joined(nick);
	proto.joined(it.first->get_nick());
	it.first->add_obstacle(m_player);
      }
    } 
  }

  //suite a la reception de l'info sur la rotation de l'arme d'un client
  void session_on_server::do_rotate(int angle){
    for(auto it : players) {
      if(it.first != m_player) {  
	it.second->proto.rotated( angle, nick);
      }
    }
  }

  void session_on_server::send_other_new_bullet(int x_s, int y_s){

    for(auto it : players) {
      int i = m_player->get_ammo()->get_nb()-1;
      int x = (*m_player->get_ammo())[i]->get_x();
      int y = (*m_player->get_ammo())[i]->get_y();
      int id = (*m_player->get_ammo())[i]->get_id();
      stringstream ss(nick);
      ss << id;
      it.second->proto.addBullet(ss.str(), x, y, x_s, y_s);
    }
  }
  


  //suive a l'event de tir du client
  void session_on_server::do_shoot(int x1, int y1,int x2, int y2 ){
    ezlock hold (ez_mutex);
    int anc_id = cur_id;
    m_player->get_ammo()->shoot(x1,x2,y1,y2,cur_id);
    if(cur_id != anc_id)
      send_other_new_bullet(x2,y2);
    int nb = m_player->get_ammo()->get_NbAmmo();
    last_ammo_size = m_player->get_ammo()->get_NbAmmo();
    proto.nbAmmo(nb);
  }



  void session_on_server::do_quit() {
    for( auto it : players) {
      if(it.first->get_nick() != nick) {
	it.second->proto.left(nick);
      } else {
	pthread_mutex_lock(&mutex);	
	players_to_delete.push_back(it.first);
	pthread_mutex_unlock(&mutex);
      }
    }	
  }

  void * master_th(void * args) {
    while(1) {
      SDL_Delay(40);
      ezlock hold(ez_mutex);
      //on appel pass row de chaque item savoir si ils sont en collision avec un joueur
      for(int i = 0; i < map_server.get_Item_vec().size(); i++) {
	map_server.get_Item(i).pass_row();
	bool showed = map_server.get_Item(i).get_just_showed();
	if(map_server.get_Item(i).hidden() || showed) {

	  for(auto it: players) {
	    if(showed) {
	      it.second->proto.showItem(i);
	    }
	    if(map_server.get_Item(i).hidden()) {
	      it.second->proto.hideItem(i);
	    }
	  }
	}
      }
    }
  }


};


//boucle pour supprimer tout les joueur qui ont quitter la partie
void * boucle_suppr(void * arg) {
  while(1) {
    if(Teelol::players_to_delete.size() != 0) {
      pthread_mutex_lock(&mutex);
      auto it = Teelol::players.find(Teelol::players_to_delete[Teelol::players_to_delete.size() - 1]);
      Teelol::players.erase(it);
      Teelol::players_to_delete.pop_back();

      /* Pour chaque player, on supprime la collision avec le player supprimé */
      for(auto itp : Teelol::players) {
	itp.first->delete_obstacle(it->first);
      }

      pthread_mutex_unlock(&mutex);
    }
  }
}



void boucle_Inter(int argc,char ** argv){
  pthread_t thread_master;
  pthread_create(&thread_master, NULL, Teelol::master_th, (void*)NULL);
  netez::server<Teelol::session_on_server> server(argc,argv);
  bool quit = false;
  while(!quit){
    stringstream ss;
    cout<<"[What is your command?]>";
    char buf[256];
    cin.getline(buf,256);
    ss << buf;
    string cmd;
    ss >> cmd;
    if(cmd == "quit") quit = true;
    else cout<<"command not found"<<endl;
  }
  for (auto it = Teelol::players.begin() ; it != Teelol::players.end() ; it++){
    it->second->finish();
  }

}


string get_map_name(int argc, char ** argv){
  string map = "map.lvl";
  for (int i = 1 ; i < argc ; i++){
    string op = argv[i];
    if(op == "-P")
      {
	i++;
      }
    else map = op;
  }
  return map;
}

bool launch_server() {
    Ecran sc(400,400);
    Event e;
    Button ok("ok", 10,300, 25,380);
    ListView lv(10,10,280,370,30);
    Teelol::map_server.load_Map_Name();
    for( auto it : Teelol::map_server.get_Map_Name()) {
	lv.add_Item(new ListItem(it));
    }
    while(!e[QUIT] && !ok.getClicked()) {
	e.UpdateEvent();
	sc.clean();
	lv.pass_row(e);
	lv.show(&sc);
	ok.pass_row(e);
	ok.show(&sc);
	sc.Flip();
    }
    if(lv.selected()) {
	Teelol::map_server.set_Map_Name(lv.selected()->text());
    }
    else {
	Teelol::map_server.set_Map_Name("../const/map.lvl");
    }
    if(!e[QUIT]) {
	return true;
    }
    return false;
}





int main(int argc, char ** argv){
  
  srand(time(NULL));
  string path = "../const/";
  string map = path + get_map_name(argc, argv);
  if(launch_server()) {
      
      Teelol::map_server.load_Map();
      pthread_t th_boucle_suppr;
      pthread_create(&th_boucle_suppr, NULL, boucle_suppr, (void*)NULL);
      boucle_Inter(argc, argv);
      pthread_cancel(th_boucle_suppr);
  }
}
				
