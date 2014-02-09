#ifndef _FOCUS
#define _FOCUS

#include "Focusable.hh"
#include <vector>

class Focuser {
public:
    void operator()(int);
    void add_focusable(Focusable * t);


private:
    std::vector<Focusable*> m_focusable;

};



#endif
