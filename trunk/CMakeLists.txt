PROJECT(Teelol CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client client.cc player.cc gr/Event.cc gr/Collision.cc gr/Ecran.cc gr/Form.cc gr/Character.cc gr/Const.cc gr/Bullet.cc gr/Ammo.cc gr/Rotable.cc gr/Item.cc gr/Parse.cc gr/Interface/Button.cc gr/Interface/Text.cc gr/Notif.cc IA/Ia.cc gr/Interface/Focuser.cc)


ADD_EXECUTABLE(server server.cc player.cc gr/Event.cc gr/Collision.cc gr/Ecran.cc gr/Form.cc gr/Character.cc gr/Const.cc gr/Bullet.cc gr/Ammo.cc gr/Rotable.cc gr/Item.cc gr/Parse.cc gr/Interface/Button.cc gr/Interface/Text.cc gr/Notif.cc Map.cc IA/Ia.cc gr/Interface/ListView.cc gr/Interface/ListItem.cc gr/Interface/ScrollBar.cc)

TARGET_LINK_LIBRARIES(client -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf)

TARGET_LINK_LIBRARIES(server -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf)
