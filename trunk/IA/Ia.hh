#ifndef _IA
#define _IA

#include "../gr/Form.hh"
#include <iostream>
#include "../gr/Collision.hh"

class Ia: public Form {

public:

    Ia(int x, int y, int h, int l);

    virtual void die();

    virtual void respawn();

    virtual void shoot();

    collision_t collide();
    
    virtual void pass_row();
    
    virtual type_t get_type();
    
    

    virtual void add_obstacle(Form * f);
    
    virtual void delete_obstacle(Form * f);

protected:
    int m_wait, m_dmg;
    std::vector <Form *> m_obstacle;
};




#endif
