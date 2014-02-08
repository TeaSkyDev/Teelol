#ifndef _LISTITEM
#define _LISTITEM

#include "../Event.hh"
#include <boost/signals2.hpp>
#include <iostream>

using boost::signals2::signal;


#define signals /**/

class ListItem {

public:

    ListItem(std::string text);
    void pass_row(Event &e);
				 
    int & x();
    int &y();
    int &h();
    int &l();


private:
    bool is_inside(int, int);
    
    std::string m_text;
    bool m_clicked, m_double_clicked;
    int m_delay;
    int m_x, m_y, m_h, m_l;
			  
public signals:

    signal<void()> clicked;
    signal<void()> double_clicked;


};



#endif
