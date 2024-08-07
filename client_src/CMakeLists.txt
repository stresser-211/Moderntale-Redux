cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "/W0 /O2 /EHsc")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "/W0 /O2 /EHsc")

set(mtx "Moderntale_Redux")
set(mtx_src
    "game/nodes/button.hpp"
    "game/nodes/object.hpp"
    "game/nodes/room.hpp"
    "game/scenes/menu.hpp"
    "game/asio.hpp"
    "game/functions.hpp"
    "game/game.cpp"
    "game/global.hpp"
    "game/incl.hpp"
    "game/init.hpp"
    "game/io.hpp"
    "game/locale.hpp"
)
set(tcp "net_transfer")
set(tcp_src
    "net_transfer/consts.h"
    "net_transfer/main.h"
    "net_transfer/main.c"
)

add_library(${tcp} ${tcp_src})
add_executable(${mtx} ${mtx_src})

target_link_options(${mtx} PRIVATE
    "/SUBSYSTEM:WINDOWS"
)
target_link_options(${tcp} PRIVATE
    "/DLL"
)

include_directories("D:/DIMA/ALL/SDK/SDL2/include")

target_link_libraries(${tcp} PUBLIC
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2_net.lib"
)
target_link_libraries(${mtx} PUBLIC
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2.lib"
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2main.lib"
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2_image.lib"
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2_mixer.lib"
    "D:/DIMA/ALL/SDK/SDL2/lib/x64/SDL2_ttf.lib"
    ${tcp}
)
