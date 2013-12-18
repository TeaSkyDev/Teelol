#include "Ecran.hh"
#include "Event.hh"
#include "Character.hh"
#include "Bullet.hh"


struct affichable{
  vector<Form *> form;
  Ecran * e;

  void ajoute_forme(Form * f){form.push_back(f); continuer = true;}
  bool continuer;
};


void * affiche(void * arg){
  affichable * a = (affichable*)arg;
  while(a->continuer){
    a->e->clean();
    for(int i = 0 ; i < a->form.size() ; i++)
      a->form[i]->show();
    a->e->Flip();
    SDL_Delay(10);
 }
}


void routine(){

  Ecran sc(400,400);
  affichable a;
  a.e = &sc;
  Event e;
  Character r("../img/tee.png",50,20,10,10,&sc);
  Character f ("../img/Mur.png", 20,200,300,10, &sc);
  r.add_obstacle(&f);
  a.ajoute_forme(&f);
  a.ajoute_forme(&r);
  pthread_t th;
  pthread_create(&th,NULL, affiche, (void*)&a);
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
      f.set_x(e().m_x);
      f.set_y(e().m_y);
    }
    r.pass_row();
    SDL_Delay(50);
  }
  a.continuer = false;
}



int main(){
  routine();
  return 0;
}
