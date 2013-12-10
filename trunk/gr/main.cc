#include "Ecran.hh"
#include "Character.hh"


void routine(){
  Ecran e(300,300);
  string action;
  Character r("",10,10,10,10,&e);
  Character r2("",10,290,300,10,&e);
  r.add_obstacle(r2);
  SDL_Event ev;
  while(1){
    SDL_PollEvent(&ev);
    if(ev.type == SDL_KEYDOWN){
      if(ev.key.keysym.sym == SDLK_LEFT)
	      r.move_left();
      if(ev.key.keysym.sym == SDLK_RIGHT)
	      r.move_right();
      if(ev.key.keysym.sym == SDLK_SPACE)
	      r.jump();
      if(ev.key.keysym.sym == SDLK_DOWN)
	{
	  r.stop_x();
	  r.stop_y();
	}
      if(ev.key.keysym.sym == SDLK_ESCAPE)
	break;
    }
    r.pass_row();
    r.show();
    
    r2.show();
    // r3.show();
    e.clean();
    SDL_Delay(50);
  }

}



int main()
{
  routine();
  return 0;
}
