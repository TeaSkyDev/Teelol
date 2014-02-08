#ifndef _LISTVIEW
#define _LISTVIEW

#include <iostream>
#include <vector>
#include "../Ecran.hh"
#include "../Event.hh"
#include "ListItem.hh"
#include "ScrollBar.hh"

#define slots /**/

class ListView {
public:
    
    ListView(int x, int y, int h, int l, int = 5);
    
    void add_Item(ListItem *item);

    void pass_row(Event & e);
    void show(Ecran * sc);



    

private:
    int m_x, m_y, m_h, m_l;
    std::vector<ListItem*> m_item;
    ScrollBar m_bar;
    int m_xb, m_yb;
    int m_item_h;
		

public slots:
    void scroll(int);
    void clicked(int);
    
signals

    signal<void(int)> scrolled;
};




#endif
