#ifndef _FOCUS
#define _FOCUS

#include "Focusable.hh"
#include "../Event.hh"
#include <vector>

class Focuser {
public:

    Focuser();
    void operator()(int);
    void add_focusable(Focusable * t);
    void pass_row(Event & e);

private:
    std::vector<Focusable*> m_focusable;
    int m_select, m_delay;
    
};



#endif
