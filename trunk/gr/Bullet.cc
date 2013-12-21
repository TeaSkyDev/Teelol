#include "Bullet.hh"


Bullet::Bullet(int x, int y, int h, int l, int dmg, int x_s, int y_s, string img):Form(x,y,h,l), m_dmg(dmg) {
  set_image(img); 
  //m_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, h, l, 32, 0, 0, 0, 0);
 
  m_vy  = 0;
  m_vx  = 0;
  m_x_init = x_s;
  m_y_init = y_s;
  int o = m_x_init - m_x;
  int p = m_y_init - m_y;
  m_angle = atan2(p,o);
  int speed_init = sqrt(o*o+p*p) * 2;

  m_vx = speed_init*cos(m_angle);
  m_vy = speed_init*sin(m_angle);

}


int Bullet::get_dmg(){
  return m_dmg;
}

type_t Bullet::get_type() {
  return BULLET;
}

void Bullet::pass_row(){
  
  double g  = 9.81;
  m_vy+=0.5;

  //m_x = m_x_init;
  //m_y = m_y_init;
  m_y += m_vy;
  m_x += m_vx;

  m_temps += 8;

  bool continuer = true;

  /*for(int i = 0 ; i < abs(m_speed.m_y) ; i++){
    direction_t d = collide();
    if(d.col_y == NORTH || d.col_y == SOUTH){
      explode();
      continuer = false;
    }*/
   
  /* if(m_speed.m_y > 0)
      m_y += m_speed.m_y * m_temps;
    else m_y -= m_speed.m_y * m_temps;*/
  /*}
  for(int i = 0 ; i < abs(m_speed.m_x) && continuer; i++){
    direction_t d = collide();
    if(d.col_x == EAST || d.col_x == WEST){
      explode();
    }*/

   /* if(m_speed.m_x > 0)
      m_x += m_speed.m_x * m_temps;
    else
      m_x -= m_speed.m_y * m_temps;*/
  //}
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
