cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

project(r-type)

set(LIB_GAME_ENGINE gameengine)
set(BINARY_SERVER r-type_server)
set(BINARY_CLIENT r-type_client)
set(SRC_SERVER src/server)
set(SRC_SERVER_GAME src/server/game_server)
set(SRC_CLIENT src/client)

if (WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

set(FILE_SERVER ${SRC_SERVER}/main.cpp ${SRC_SERVER}/Client.cpp ${SRC_SERVER}/Lobby_session.cpp ${SRC_SERVER}/Room.cpp ${SRC_SERVER}/Server.cpp ${SRC_SERVER}/Logic.cpp ${SRC_SERVER}/Serializer.cpp ${SRC_SERVER}/Clock.cpp)
set(FILE_SERVER_GAME ${SRC_SERVER_GAME}/Player.cpp ${SRC_SERVER_GAME}/Bullet.cpp ${SRC_SERVER_GAME}/Mob.cpp ${SRC_SERVER_GAME}/Kamikaze.cpp ${SRC_SERVER_GAME}/TIEHunter.cpp ${SRC_SERVER_GAME}/Boss.cpp  ${SRC_SERVER_GAME}/MiniBoss.cpp)
set(FILE_CLIENT ${SRC_CLIENT}/main.cpp ${SRC_CLIENT}/condition_game_loop.cpp ${SRC_CLIENT}/custom_func_button.cpp ${SRC_CLIENT}/custom_func_gameloop.cpp ${SRC_CLIENT}/custom_func_input.cpp ${SRC_CLIENT}/custom_func_network.cpp ${SRC_CLIENT}/custom_func_text.cpp ${SRC_CLIENT}/game_running_network.cpp ${SRC_CLIENT}/interpolation.cpp)


################################################

include_directories(includes/server)
include_directories(includes/game)
#include_directories(../Game_engine/includes/)
#include_directories(../Game_engine/includes/System)
#nclude_directories(../Game_engine/includes/System/Network)


#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
#set(EXECUTABLE_OUTPUT_PATH .)

add_subdirectory(../Game_engine libgameengine_build)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) #Lorsque qu'on installe conan cela génère conanbuildinfo.cmake. Il ne modifie pas l'environnement, il fournit simplement des variables conan et des macros supplémentaires.
conan_basic_setup()     #Macro qui définira essentiellement les répertoires d'inclusion, les répertoires de bibliothèques, les définitions, etc.

add_executable(${BINARY_SERVER} ${FILE_SERVER} ${FILE_SERVER_GAME})
add_executable(${BINARY_CLIENT} ${FILE_CLIENT})

#message(${CONAN_LIBS})

#target_link_libraries(${BINARY_SERVER} sfml-audio sfml-graphics sfml-system sfml-window ${CONAN_LIBS} gameengine)
#target_link_libraries(${BINARY_CLIENT} sfml-audio sfml-graphics sfml-system sfml-window ${CONAN_LIBS} gameengine)

#find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(${BINARY_SERVER} ${CONAN_LIBS} gameengine)
target_link_libraries(${BINARY_CLIENT} ${CONAN_LIBS} gameengine)