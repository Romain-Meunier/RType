cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

project(game-engine)

set(LIB_GAME_ENGINE gameengine)
set(SRC_GE src/)
set(SRC_GE_SYSTEM src/System)
set(SRC_GE_COMPONENT src/Component)
set(SRC_GE_SYSTEM_NETWORK src/System/Network)


set(FILE_GE ${SRC_GE}/Game_engine.cpp ${SRC_GE}/Entity.cpp ${SRC_GE}/create_entity.cpp ${SRC_GE}/config_comp.cpp)
set(FILE_GE_SYSTEM ${SRC_GE_SYSTEM}/Eventsystem.cpp ${SRC_GE_SYSTEM}/Rendersystem.cpp ${SRC_GE_SYSTEM}/Soundsystem.cpp)
set(FILE_GE_SYSTEM_NETWORK ${SRC_GE_SYSTEM_NETWORK}/Network.cpp ${SRC_GE_SYSTEM_NETWORK}/Deserializer.cpp)
set(FILE_GE_COMPONENT ${SRC_GE_COMPONENT}/Movement_component.cpp ${SRC_GE_COMPONENT}/Clock_component.cpp ${SRC_GE_COMPONENT}/Drawable_component.cpp ${SRC_GE_COMPONENT}/Drawable_impl.cpp ${SRC_GE_COMPONENT}/Input_component.cpp ${SRC_GE_COMPONENT}/Mouse_hitbox_component.cpp ${SRC_GE_COMPONENT}/Sound_component.cpp ${SRC_GE_COMPONENT}/Sound_impl.cpp ${SRC_GE_COMPONENT}/Text_component.cpp ${SRC_GE_COMPONENT}/Text_impl.cpp)
#########################################


#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
# set(EXECUTABLE_OUTPUT_PATH .)
#find_package(asio REQUIRED)
#find_package(boost REQUIRED)
#find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
#find_package(raylib REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) #Lorsque qu'on installe conan cela génère conanbuildinfo.cmake. Il ne modifie pas l'environnement, il fournit simplement des variables conan et des macros supplémentaires.
conan_basic_setup()     #Macro qui définira essentiellement les répertoires d'inclusion, les répertoires de bibliothèques, les définitions, etc.

add_library(${LIB_GAME_ENGINE} STATIC ${FILE_GE} ${FILE_GE_SYSTEM} ${FILE_GE_COMPONENT} ${FILE_GE_SYSTEM_NETWORK})
target_include_directories(${LIB_GAME_ENGINE} PUBLIC includes)
target_link_libraries(${LIB_GAME_ENGINE} ${CONAN_LIBS})
#SET(APP_EXE StaticTest)
#ADD_EXECUTABLE(${APP_EXE} main.cpp)
#TARGET_LINK_LIBRARIES(${APP_EXE} ${CONAN_LIBS} ${LIB_GAME_ENGINE})
