cmake_minimum_required (VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "/W0 /O2 /EHsc")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "/W0 /O2")

set(OUT_DIR "../../../../")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")

set(mtx "mtx")
set(tcp "net_transfer")
set(srv "server")

add_library(${tcp} SHARED "net_transfer/main.c")
add_executable(${mtx} "client/game/game.cpp")
add_executable(${srv} "server/main.c")

target_link_options(${mtx} PRIVATE
	"/SUBSYSTEM:WINDOWS"
)
target_link_options(${tcp} PRIVATE
	"/DLL"
)
target_link_options(${srv} PRIVATE
	"/SUBSYSTEM:CONSOLE"
)

include_directories(
	"D:/DIMA/ALL/SDK/SDL2/include"
	"D:/DIMA/ALL/SDK/parson"
)

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
target_link_libraries(${srv} PUBLIC
	${tcp}
)

set_target_properties(${mtx} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client/engine")
set_target_properties(${tcp} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client/engine")
set_target_properties(${srv} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/server/.root")
