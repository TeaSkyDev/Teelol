#ifndef _LABEL
#define _LABEL

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include "../Ecran.hh"

class Label {

public:
    Label(int x, int y, std::string);
    void show(Ecran * sc);

private:
    
    TTF_Font *m_font;
    SDL_Surface * m_content;
    int m_x, m_y;
    std::string m_text;

};





#endif
