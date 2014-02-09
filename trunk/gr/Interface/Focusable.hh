#ifndef _FOCUSABLE
#define _FOCUSABLE

#include <boost/signals2.hpp>
using boost::signals2::signal;

class Focusable {

public:

    Focusable() {
	m_id = STATID++;
    }


    virtual void set_focus(bool f){
	m_focus = f;
    }

    int getId() {
	return m_id;
    }

    signal<void(int)> focused;

protected:

    bool m_focus;
    int m_id;
    static int STATID;
};






#endif
