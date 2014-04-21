#ifndef _PROTO_HH_
#define _PROTO_HH_

#include "netez.hh"

namespace Teelol {

  using namespace netez;

  struct m_proto : public protocol<> {

    message<1,void()> ping;
    message<2,void()> pong;

    m_proto(socket & io) : protocol<>(io), ping(this), pong(this) {
    }

  };
};
#endif
