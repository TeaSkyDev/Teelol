#include "Master.hh"
using namespace std;


namespace Teelol {

    Master::Master(int argc, char ** argv) {
	if ( launch_server() ) {
	    map_server.load_Map();
	    boucle_Inter(argc, argv);
	}
    }


    bool Master::launch_server() {
	Ecran sc(400, 400);
	Event e;
	Button ok("ok", 10, 300, 25, 380);
	ListView lv(10,10,280,370,30);
	map_server.load_Map_Name();
	for ( auto it : map_server.get_Map_Name() ) {
	    lv.add_Item(new ListItem(it));
	}
	while ( !e[QUIT] && !ok.getClicked() ) {
	    e.UpdateEvent();
	    sc.clean();
	    lv.pass_row(e);
	    lv.show(&sc);
	    ok.pass_row(e);
	    ok.show(&sc);
	    sc.Flip();
	}
	if ( lv.selected()) {
	    map_server.set_Map_Name(lv.selected()->text());
	} else {
	    map_server.set_Map_Name("../const/map.lvl");
	}
	if ( !e[QUIT] ) {
	    return true;
	} else {
	    return false;
	}
    }

    void Master::boucle_Inter(int argc, char ** argv) {
	netez::server<session_on_server> server(argc, argv);
	while (!m_quit) {
	}
    }


    void Master::new_session(session_on_server& s, Player & p ) {
	if ( first_team.size() >= second_team.size() ) {
	    second_team[&p] = &s;
	} else {
	    first_team[&p] = &s;
	}
	s.connection.connect(boost::bind(&Master::session_connect, this, _1, _2));
	/*	s.move.connect(boost::bind(&Master::session_move, this, _1, _2));
	s.shoot.connect(boost::bind(&Master::session_shoot, this, _1, _2, _3, _4));
	s.quit.connect(boost::bind(&Master::session_quit, this));*/
    }



    void Master::session_connect( string nick , Player * p ) {
	bool trouve = false;
	for ( auto it : nick_map ) {
	    if (it.second == nick) {
		trouve = true;
		nick_refused();
	    }
	}
	if ( !trouve ) {
	    nick_map[p] = nick;
	    nick_accept();
	}
    }


};


int main(int argc, char ** argv) {
    Teelol::Master m(argc, argv);
}
