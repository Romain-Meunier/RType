/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival
** File description:
** macro
*/

#pragma once

#include <string>

#ifdef _WIN32

#define PATH_ASSET_GRAPH std::string("Release/assets/graphic_2D/")
#define PATH_ASSET_FONT std::string("Release/assets/font/")
#define PATH_ASSET_AUDIO std::string("Release/assets/audio/")
#define PATH_ASSET_PATTERN std::string("Release/assets/pattern/")

#endif //_WIN32

#ifdef linux

#define PATH_ASSET_GRAPH std::string("assets/graphic_2D/")
#define PATH_ASSET_FONT std::string("assets/font/")
#define PATH_ASSET_AUDIO std::string("assets/audio/")
#define PATH_ASSET_PATTERN std::string("assets/pattern/")


#endif //linux

#ifdef __APPLE__

#define PATH_ASSET_GRAPH std::string("assets/graphic_2D/")
#define PATH_ASSET_FONT std::string("assets/font/")
#define PATH_ASSET_AUDIO std::string("assets/audio/")
#define PATH_ASSET_PATTERN std::string("assets/pattern/")

#endif //__APPLE__
