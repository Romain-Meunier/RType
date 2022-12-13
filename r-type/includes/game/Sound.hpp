/*
** EPITECH PROJECT, 2022
** Sound.hpp
** File description:
** r-type
*/

#pragma once

#include "macro.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class Sound {
    public:
        Sound(std::string name = "None") {
            std::cout << name.compare("None") << std::endl;
            if (name.compare("None") != 0) {
                sb.loadFromFile(PATH_ASSET_AUDIO.append(name));
                s.setBuffer(sb);
            }
        }
        ~Sound() {}
        void load_from_file(std::string file) {sb.loadFromFile(PATH_ASSET_AUDIO.append(file));s.setBuffer(sb);}
        void setVolume(int vol) {s.setVolume((float) vol);}
        void play() 
        {
            // if (s.getStatus() == s.Stopped)
                s.play();
        }
        void stop() {s.stop();}
    private:
        sf::Sound s;
        sf::SoundBuffer sb;
};
