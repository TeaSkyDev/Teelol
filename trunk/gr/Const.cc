#include "Const.hh"
using namespace std;


Const::Const(string file){
  m_file = file;
}


void Const::load_file(){
  ifstream file(m_file.c_str());
  int img;
  string path;
   while(!file.eof()){
    file >> img;
    file >> path;
    m_path[(Image_t)img] = path;
  }
  
}


TTF_Font * Const::font(){
  return m_font;
}

string Const::operator[](Image_t img){
  auto it = m_path.find(img);
  if(it != m_path.end()){
    return it->second;
  }
}
