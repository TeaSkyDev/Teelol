#ifndef _FOCUS
#define _FOCUS

#include "Text.hh"
#include <vector>

class Focuser {
public:
    void operator()(int);
    void add_focusable(Text * t);


private:
    std::vector<Text*> m_focusable;

};



#endif
