#include "ListView.hh"


ListView::ListView(int x, int y, int h, int l, int item_h) :m_bar(x,y,h, 10){
    m_x = x + 10;
    m_h = h;
    m_l = l;
    m_y = y;
    m_item_h = item_h;
    m_bar.scroll.connect(boost::bind(&ListView::scroll, this, _1));
    select = NULL;
    m_focus = false;
}


void ListView::scroll(int purcent) {
    m_focus = true;
    double temp = purcent * ( m_item_h * m_item.size()) / 100.0f;
    for( auto it : m_item ) {
	it->y() = it->sauve_y() - temp; 
    }
    focused(m_id);
}

void ListView::pass_row(Event &e) {
    if( m_focus ) {
	if( e.getEvent().type == SDL_KEYDOWN ) {
	    if ( e.getEvent().key.keysym.sym == SDLK_UP ) {
		if( !select && m_item.size() > 0 ) {
		    clicked(m_item[m_item.size() - 1]->id());
		} else if ( m_item.size() > 0 ){
		    int i = select->id();
		    i--;
		    if( i == -1 ) {
			i = m_item.size() - 1;
		    }
		    clicked(i);
		}
		for( auto it : m_item ) {
		    it->y() = it->sauve_y() - select->sauve_y() + m_y; 
		}	    
	    } else if ( e.getEvent().key.keysym.sym == SDLK_DOWN ) {
		if ( !select && m_item.size() > 0 ) {
		    clicked(m_item[0]->id());
		} else if ( m_item.size() > 0 ) {
		    int i = select->id();
		    i++;
		    if ( i == m_item.size() ) {
			i = 0;
		    }
		    clicked(i);
		}
		for( auto it : m_item ) {
		    it->y() = it->sauve_y() - select->sauve_y() + m_y; 
		}	    
	    } 

	}
    }
    for (auto it : m_item ) {
	it->pass_row(e);
    }
    m_bar.pass_row(e);
}

void ListView::clicked(int i) {
    m_focus = true;
    for (auto it : m_item ) {
	if( it->id() == i ) {
	    it->r() = 0;
	    it->g() = 255;
	    it->b() = 255;
	    select = it;
	} else {
	    it->r() = 255;
	    it->g() = 255;
	    it->b() = 255;
	}
    }
    focused(m_id);
}

void ListView::add_Item(ListItem * item) {
    m_item.push_back(item);
    m_item[m_item.size() - 1]->id() = m_item.size() - 1;
    m_item[m_item.size() - 1]->h() = m_item_h;
    m_item[m_item.size() - 1]->l() = m_l;
    m_item[m_item.size() - 1]->x() = m_x;
    m_item[m_item.size() - 1]->set_y((m_item.size() - 1) * m_item_h + m_y);
    m_item[m_item.size() - 1]->clicked.connect(boost::bind(&ListView::clicked, this, _1));
    if( m_item_h * m_item.size() > m_h) {
	m_bar.grown(m_h * 100/(m_item_h * m_item.size()));
    }
    scroll(0);
    m_focus = false;
}

void ListView::show(Ecran * sc) {
    int i = 0;
    SDL_Surface * fond = SDL_CreateRGBSurface(SDL_HWSURFACE, m_l, m_h, 32, 0,0,0,0);
    SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 255,200,255));
    SDL_Rect r;
    r.x = m_x; r.y = m_y;
    sc->put(fond, r);
    SDL_Rect rect2;
    for ( auto it : m_item ) {
	SDL_Surface * elem = SDL_CreateRGBSurface(SDL_HWSURFACE, it->l(), it->h(), 32, 0,0,0,0);
	SDL_FillRect(elem, NULL, SDL_MapRGB(elem->format, it->r(), it->g(), it->b()));
	SDL_Surface * text = TTF_RenderText_Blended(it->police(), it->text().c_str(), it->color());
	SDL_Rect rect;
	rect.x = m_x;
	rect.y = it->y();
	it->hide(false);
	rect2.x = 0;
	rect2.y = 0;
	rect2.w = it->l();
	rect2.h = it->h();
	if ( m_y + m_h < it->y() + it->h() ) {
	    rect2.h = m_y + m_h - it->y();
	    if(rect2.h < 0 || it->y() > m_y + m_h) {
		rect2.h = 0;
		it->hide(true);
	    }
	}
	if ( it->y() < m_y ) {
	    if(it->y() + it->h() < m_y) {
		rect2.h = 0;
		it->hide(true);
	    } else {
		rect2.h = (it->y() + it->h() - m_y);
		rect2.y = it->h() - rect2.h;
		rect.y = m_y;
	    }
	}
	sc->put(elem, rect, rect2);
	rect.x += 5;
	sc->put(text, rect, rect2);
	SDL_FreeSurface(elem);
	SDL_FreeSurface(text);
    }
    SDL_FreeSurface(fond);
    m_bar.show(sc);
}

ListItem *ListView::selected() {
    return select;
}
