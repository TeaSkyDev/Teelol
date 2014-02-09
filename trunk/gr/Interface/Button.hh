#ifndef _BUTTON
#define _BUTTON

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include "../Event.hh"
#include "../Ecran.hh"
#include <SDL/SDL_ttf.h>
#include <boost/signals2.hpp>
using boost::signals2::signal;
class Button{
public:
    Button(std::string, int, int ,int ,int);
  
    void pass_row(Event&);
    bool getClicked();
    void show(Ecran *);
    int &x();
    int &y();
    int &h();
    int &l();

    ~Button();
    
    //slot:
    
    
    //signal doivent être publique
    signal<void()> pressed;
    signal<void()> clicked;
    signal<void()> hover;


private:

    bool is_inside(int, int);
    bool m_hover;
    SDL_Surface * m_form, *m_fond;
    int m_x, m_y, m_h, m_l; 
    std::string m_text;
    bool m_clicked;
};


#endif
