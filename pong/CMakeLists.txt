cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

project(pong)

set(LIB_GAME_ENGINE gameengine)
set(BINARY pong)
set(BINARY_SERVER server)
set(SRC src/game/)
set(SRC_SERVER src/server)
set(SRC_SERVER_GAME src/server/game)


if (WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

set(FILE_SRC ${SRC}/main.cpp ${SRC}/custom_func_loop.cpp ${SRC}/check_hitbox.cpp ${SRC}/game_running_network.cpp ${SRC}/custom_func_button.cpp ${SRC}/custom_func_input.cpp ${SRC}/custom_func_network.cpp)
set(FILE_SRC_SERVER ${SRC_SERVER}/main.cpp ${SRC_SERVER}/Client.cpp ${SRC_SERVER}/Clock.cpp ${SRC_SERVER}/Lobby_session.cpp ${SRC_SERVER}/Logic.cpp ${SRC_SERVER}/main.cpp ${SRC_SERVER}/Room.cpp ${SRC_SERVER}/Serializer.cpp ${SRC_SERVER}/Server.cpp ${SRC_SERVER}/Clock.cpp)
set(FILE_SRC_SERVER_GAME ${SRC_SERVER_GAME}/Player.cpp ${SRC_SERVER_GAME}/Ball.cpp)

################################################

include_directories(includes)
include_directories(includes/server)
include_directories(includes/server/game)

add_subdirectory(../Game_engine libgameengine_build)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) #Lorsque qu'on installe conan cela génère conanbuildinfo.cmake. Il ne modifie pas l'environnement, il fournit simplement des variables conan et des macros supplémentaires.
conan_basic_setup()     #Macro qui définira essentiellement les répertoires d'inclusion, les répertoires de bibliothèques, les définitions, etc.

add_executable(${BINARY} ${FILE_SRC})

target_link_libraries(${BINARY} ${CONAN_LIBS} gameengine)

add_executable(${BINARY_SERVER} ${FILE_SRC_SERVER} ${FILE_SRC_SERVER_GAME})
target_link_libraries(${BINARY_SERVER} ${CONAN_LIBS} gameengine)