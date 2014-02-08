#include "ListView.hh"


ListView::ListView(int x, int y, int h, int l, int item_h) :m_bar(x,y,h, 10){
    m_x = x + 10;
    m_h = h;
    m_l = l;
    m_y = y;
    m_item_h = item_h;
    m_bar.scroll.connect(boost::bind(&ListView::scroll, this, _1));
}


void ListView::scroll(int purcent) {
    double temp = purcent * ( m_item_h * m_item.size()) / 100.0f;
    for( auto it : m_item ) {
	it->y() = it->sauve_y() - temp; 
    }
}

void ListView::pass_row(Event &e) {
    for (auto it : m_item ) {
	it->pass_row(e);
    }
    m_bar.pass_row(e);
}

void ListView::clicked(int i) {
    //cout<<"item " << i << " a ete clique" << endl;
}

void ListView::add_Item(ListItem * item) {
    m_item.push_back(item);
    m_item[m_item.size() - 1]->id() = m_item.size() - 1;
    m_item[m_item.size() - 1]->h() = m_item_h;
    m_item[m_item.size() - 1]->l() = m_l;
    m_item[m_item.size() - 1]->set_y((m_item.size() - 1) * m_item_h + m_y);
    m_item[m_item.size() - 1]->clicked.connect(boost::bind(&ListView::clicked, this, _1));
    if( m_item_h * m_item.size() > m_h) {
	m_bar.grown(m_h * 100/(m_item_h * m_item.size()));
    }
    scroll(0);
}

void ListView::show(Ecran * sc) {
    int i = 0;
    SDL_Surface * fond = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_h, 32, 0,0,0,0);
    SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 255,200,255));
    SDL_Rect r;
    r.x = m_x; r.y = m_y;
    sc->put(fond, r);
    for ( auto it : m_item ) {
	SDL_Surface * text = TTF_RenderText_Blended(it->police(), it->text().c_str(), it->color());
	SDL_Rect rect;
	rect.x = m_x;
	rect.y = it->y();
	sc->put(text, rect);
	SDL_FreeSurface(text);
    }
    SDL_FreeSurface(fond);
    m_bar.show(sc);
}
