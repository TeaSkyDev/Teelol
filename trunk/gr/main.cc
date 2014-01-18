#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"
#include "Parse.hh"


void routine(){

  Ecran sc(500,500);
  Parse p(240,240);
  Event e;
  Character r(I_TEE_P,50,20,10,10,&sc);
  Character r2(I_TEE_P, 50,20,10,10,&sc);
  Form f (20,200,10,300);
  Form f2 (40,221,10,300);
  Form f3 (75,200,10,300);
  f.set_screen(&sc);
  f2.set_screen(&sc);
  f3.set_screen(&sc);
  f.set_image(I_MUR);
  f2.set_image(I_MUR);
  f3.set_image(I_MUR);


  /* On ajoute le mur et la balle dans la liste de collisions */
  r << f;
  r << f2;
  r << f3;


  while(!e[QUIT]){
    e.UpdateEvent();
    if(e[LEFT])
      r.move_left();
    else if(e[RIGHT])
      r.move_right();
    else r.stop_x();
    if(e[JUMP]) {
      r.jump();
      e.reset_pressed(JUMP);
    }

    if(e[LEFT_CL]){
      r.shoot();
    }
    if(!e[LEFT_CL])
      sc.clean();
    r.pass_row();
    cout<<r.get_x() << " " <<r.get_y()<<endl;
    point poi = p.parse_this(&r, r.get_x(), r.get_y());
    r.get_weapon()->set_angle(-atan2(e().m_x-240, e().m_y-240)*180/M_PI+90);
    r.get_weapon()->rotate(0, 250, 250, 10);    
    r.show(poi.x, poi.y);
    r.get_weapon()->show();
    poi = p.parse_this(&f, r.get_x(), r.get_y());
    f.show(poi.x, poi.y);
    poi = p.parse_this(&f2, r.get_x(), r.get_y());
    f2.show(poi.x, poi.y);
    poi = p.parse_this(&f3, r.get_x(), r.get_y());
    f3.show(poi.x, poi.y);
    sc.Flip();
    SDL_Delay(50);
  }

}



int main(){
  routine();
  return 0;
}
