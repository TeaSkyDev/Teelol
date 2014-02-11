#include "Label.hh"
using namespace std;

Label::Label(int x, int y, string text) {
    TTF_Init();
    m_font = TTF_OpenFont("../const/Font.ttf", 15);
    SDL_Color col = {0,0,0};
    m_text = text;
    m_content = TTF_RenderText_Blended(m_font, m_text.c_str(), col);
    m_x = x; 
    m_y = y;
}


void Label::show(Ecran * sc) {
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    sc->put(m_content, rect);
}

