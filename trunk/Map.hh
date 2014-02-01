#ifndef _MAP
#define _MAP

#include <iostream>
#include <fstream>
#include <vector>

#include "gr/Item.hh"
#include "gr/Form.hh"

struct screen_size {
  int l;
  int h;
};



class Map{
public:

  Map();
  

  void set_Map_Name(std::string);
  void load_Map_Name();
  void load_Map();
  
  Form & get_Object(int i);
  Item & get_Item(int i);
  
  std::vector<Form> &get_Object_vec();
  std::vector<Item> &get_Item_vec();

  std::vector<std::string> &get_Map_Name();

  int get_Nb_Ammo();
  
  screen_size get_Screen_Size();
  
  ~Map();
  

private:

  std::vector<Form> m_object;
  std::vector<Item> m_item;
  std::string m_name;
  std::vector<std::string> m_map_name;
  screen_size m_screen_size; 
  int m_nb_ammo;

};





#endif
