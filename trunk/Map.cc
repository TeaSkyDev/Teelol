#include "Map.hh"

using namespace std;

Map::Map(){
}


void Map::set_Map_Name(string name){
  m_name = name;
}


void Map::load_Map_Name(){
  ifstream fichier("../const/MapName");
  while(!fichier.eof()){
    string name;
    fichier >> name;
    m_map_name.push_back(name);
  }
  fichier.close();
}


void Map::load_Map(){
  ifstream fichier(m_name.c_str());
  int type, x, y, h, l, img, type2;
  fichier >> m_screen_size.l >> m_screen_size.h >> m_nb_ammo;
  while(!fichier.eof()){
    fichier >> type >> x >> y >> h >> l >> img;
    switch(type){
    case 1:
      m_object.push_back(Form(x,y,h,l));
      m_object[m_object.size()-1].set_image((Image_t)img);
      break;
    case 2:
      fichier >> type2;
      m_item.push_back(Item(x,y,h,l,(ITEM_T)type2));
      m_item[m_item.size() - 1].set_image((Image_t)img);
      break;
    }
  }
  fichier.close();
}



Form & Map::get_Object(int i){
  if(i >=0 && i < m_object.size()){
    return m_object[i];
  }
  throw i;
}

Item & Map::get_Item(int i){
  if( i >= 0 && i < m_item.size()){
    return m_item[i];
  }
  throw i;
}

vector<Item> & Map::get_Item_vec(){
  return m_item;
}

vector<Form> & Map::get_Object_vec(){
  return m_object;
}

vector<string> &Map::get_Map_Name(){
  return m_map_name;
}

screen_size Map::get_Screen_Size(){
  return m_screen_size;
}


int Map::get_Nb_Ammo(){
  return m_nb_ammo;
}

Map::~Map(){
}
