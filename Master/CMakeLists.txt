PROJECT(Teelol CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client src/client.cc)

ADD_EXECUTABLE(Master src/main.cc)

TARGET_LINK_LIBRARIES(client  -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lgr)

TARGET_LINK_LIBRARIES(Master -Wl,--copy-dt-needed-entries -lnetez -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lgr)
