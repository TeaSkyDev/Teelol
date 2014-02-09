#include "NumberEdit.hh"


NumberEdit::NumberEdit(int x, int y, int h, int l, int max, int min):m_left("<", x,y,h, 10), m_right(">",x + l - 10, y, h, 10), m_line(x + 10, y, h, l-20) {
    m_l = l;
    m_h = h;
    m_x = x;
    m_y = y;
    m_max = max;
    m_min = min;
    m_value = (m_max + m_min)/2;
    m_line.set_value(m_value);
    m_left.clicked.connect(boost::bind(&NumberEdit::decrement, this));
    m_left.pressed.connect(boost::bind(&NumberEdit::decrement, this));
    m_right.clicked.connect(boost::bind(&NumberEdit::increment, this));
    m_right.pressed.connect(boost::bind(&NumberEdit::increment, this));
    m_line.validated.connect(boost::bind(&NumberEdit::validated, this));
    m_delai = 11;
    m_focus = false;
}


void NumberEdit::decrement() {
    if( m_value > m_min ) {
	if( m_delai > 10 ) {
	    m_value --;
	    m_delai = 0;
	}
    }
    m_line.set_value(m_value);
}

void NumberEdit::increment() {
    if ( m_value < m_max ) {
	if ( m_delai > 10 ) {
	    m_delai = 0;
	    m_value ++;
	}
    }
    m_line.set_value(m_value);
}

void NumberEdit::validated() {
    m_value = m_line.getValue_int();
    if ( m_value < m_min ) {
	m_value = m_min;
	m_line.set_value( m_min );
    } else if ( m_value > m_max ) {
	m_value = m_max;
	m_line.set_value( m_max );
    }
}


void NumberEdit::pass_row(Event & e) {
    if( m_focus ) {
	m_left.pass_row(e);
	m_right.pass_row(e);
	m_line.pass_row(e);
	m_value = m_line.getValue_int();
	m_delai ++;
	if( m_delai > 20 ) {
	    m_delai = 21;
	}
    } else {
	if( is_inside(e().m_x, e().m_y) && e[LEFT_CL] ) {
	    set_focus(true);
	    focused(m_id);
	}
    }
}


void NumberEdit::show(Ecran * e) {
    m_right.show(e);
    m_left.show(e);
    m_line.show(e);
}


int NumberEdit::getValue() {
    validated();
    return m_value;
}


void NumberEdit::set_focus(bool f) {
    m_line.set_focus(f);
    m_focus = f;
}


bool NumberEdit::is_inside(int x, int y) {
    if ( x >= m_x && x <= m_x + m_l && y >= m_y && y <= m_y + m_h ) {
	return true;
    } else {
	return false;
    }
}


void NumberEdit::set_x(int x) {
    m_left.x() = x;
    m_right.x() = x + m_l - 10;
    m_line.x() = x + 10;
    m_x = x;
}

