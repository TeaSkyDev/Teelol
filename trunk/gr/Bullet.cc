#include "Bullet.hh"


Bullet::Bullet(int x, int y, int h, int l, int dmg, double angle, string img):Form(x,y,h,l), m_dmg(dmg) {
  set_image(img); 
  //m_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, h, l, 32, 0, 0, 0, 0);

  m_speed_init = 2;
  m_temps = 1;
  m_angle = angle;
  m_vy  = cos(m_angle)*m_speed_init;
  m_vx  = sin(m_angle)*m_speed_init;
  m_x_init = x;
  m_y_init = y;
}


int Bullet::get_dmg(){
  return m_dmg;
}

void Bullet::pass_row(){
  
  double g  = 9.81;
  double pi = 3.14;

  m_x = m_x_init;
  m_y = m_y_init;

  int m_xRel = (int)(m_vx*m_temps);
  int m_yRel = (int)((m_vy*m_temps) - ((g*m_temps*m_temps)/900));

  m_x += m_xRel;
  m_y -= m_yRel;

  m_temps += 8;

  /*bool continuer = true;

  m_temps += 2;

  double angle = m_angle * M_PI / 180; //50° en radians 
  m_speed.m_x *= cos(angle);
  m_speed.m_y *= -sin(angle);
  double g     = 10;

  cout << "mspeedX =" << m_speed.m_x << ", mspeedY = " << m_speed.m_y << endl;
  cout << "X =" << m_x << ", Y = " << m_y << endl;

  for(int i = 0 ; i < abs(m_speed.m_y) ; i++){
    direction_t d = collide();
    if(d.col_y == NORTH || d.col_y == SOUTH){
      explode();
      continuer = false;
    }
    if(m_speed.m_y > 0)
      m_y += m_speed.m_y * m_temps;
    else m_y -= m_speed.m_y * m_temps;
  }
  for (int i = 0 ; i < abs(m_speed.m_x) && continuer; i++){
    direction_t d = collide();
    if(d.col_x == EAST || d.col_x == WEST){
      explode();
    }
    if(m_speed.m_x > 0)
      m_x += m_speed.m_x * m_temps;
    else
      m_x -= m_speed.m_y * m_temps;
  }*/
}

void Bullet::explode(){
  set_image("img/explosion.png");
  m_speed.m_x = 0;
  m_speed.m_y = 0;
}

void Bullet::add_obstacle(Form * f){
  m_obstacle.push_back(f);
}

direction_t Bullet::collide(){
  Collision c(this, m_obstacle);
  return c.get_direction();
}


void Bullet::set_speed(int temps){
  //double angle = angle * Math.Pi / 180;
  //double angle = angle * 3.1415 / 180;

  double angle = m_angle * M_PI / 180; //50° en radians 
  m_speed.m_x *= cos(angle);
  m_speed.m_y *= -sin(angle);
  double g     = 10;

  m_speed.m_y += g * temps;
  m_x         += m_speed.m_x * temps;
  m_y         += m_speed.m_y * temps;


}

/*
// conditions initiales
    double x0 = 0, y0 = 20;
    double angle = 50 * Math.PI / 180; // 50° en radians
    double v0 = 26;
    double vx0 = v0 * Math.Cos(angle), vy0 = - v0 * Math.Sin(angle);
    double g = 10;
 
    // simulation
    double x = x0, y = y0;
    double vx = vx0, vy = vy0;
    double dt = 0.1;
 
    do
    {
        if(0 <= y && y < Console.WindowHeight * 10)
        {
            Console.CursorLeft = (int)x;
            Console.CursorTop = (int)y;
            Console.Write("a");
        }
 
        // application des équations du mouvement
        // (vx est constante)
        vy += g * dt;
        x += vx * dt;
        y += vy * dt;
    }
    while(x < Console.WindowWidth);
*/