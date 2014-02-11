PROJECT(Teelol CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client client.cc player.cc Map.cc)

ADD_EXECUTABLE(server server.cc player.cc Map.cc)

TARGET_LINK_LIBRARIES(client -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lgr)

TARGET_LINK_LIBRARIES(server -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lgr)
