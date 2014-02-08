PROJECT(Teelol CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
ADD_DEFINITIONS(-std=c++0x -ggdb)
ADD_EXECUTABLE(out main.cc Event.cc Collision.cc Ecran.cc Form.cc Character.cc Bullet.cc Ammo.cc Const.cc Rotable.cc Item.cc Parse.cc Interface/Button.cc Interface/Text.cc Menu.cc Interface/Focuser.cc Interface/ScrollBar.cc Interface/ListItem.cc Interface/ListView.cc)
TARGET_LINK_LIBRARIES(out -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf)

