#ifndef _MASTER_HH_
#define _MASTER_HH_


#include <iostream>
#include <map>
#include <vector>
#include "netez.hh"

#include <boost/signals2.hpp>

namespace Teelol {

  using boost::signals2::signal;
  using namespace std;

  template <typename S>
  struct server;
  


  template <typename S>
  class Master {
  public:
    Master(int argc, char ** argv) : m_server(argc, argv) {
      m_server.set_master(this);
    }
    
    void new_session(S * _session) {
      m_temp.push_back(_session);
      _session->master_nick.connect(boost::bind(&Master::do_nick, this, _1, _2));
    }


    void do_nick( string name , S * session) {
      bool found = false;
      for ( auto it : m_session ) {
	if ( it.first == name ) {
	  session->error("nick deja utilisé");
	  found = true;
	}
      }
      if ( !found ) {
	m_session[name] = session;
	session->success();
      }
    }

    void join() {
      m_server.join();
    }

    
  protected:
    
    std::vector<S *> m_temp;
    std::map<std::string, S *> m_session;
    server<S> m_server;

  };



  template <typename S>
  struct server : public netez::server<S> {
  
    server(int argc, char ** argv) : netez::server<S>(argc, argv) {
    }
    
    void set_master(Master<S> * m) {
      m_master = m;
    }


    virtual void work() {
      while ( ! this->closed() ) {
	auto elem = (new netez::detail::task<S>(this->_socket.accept()));
	m_master->new_session(&(*elem)._session);
	elem->start();
      }
    }
    

    Master<S> * m_master;
  };


};

#endif
