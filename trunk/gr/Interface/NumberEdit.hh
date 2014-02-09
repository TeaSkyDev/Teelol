#ifndef _NUMBEREDIT
#define _NUMBEREDIT

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "TextNumber.hh"
#include "../Event.hh"
#include "../Ecran.hh"
#include "Button.hh"
#include "Focusable.hh"

#define slots /**/

class NumberEdit : public Focusable {
public:

    NumberEdit(int, int , int, int, int max = 100, int min = 0);
    int getValue();
    void pass_row(Event &e);
    void show(Ecran *);
    void set_focus(bool);
    void set_x(int);
    

private:
    bool is_inside(int , int);
    TextNumber m_line;
    int m_max, m_min;
    int m_value;
    Button m_left, m_right;
    int m_x, m_y, m_h, m_l;
    int m_delai;

private slots:

    void increment();
    void decrement();
    void validated();

};





#endif
