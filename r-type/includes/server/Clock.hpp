/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** Clock
*/

#pragma once

#include <chrono>
#include <iostream> 

class Clock {
    public:
        Clock();
        std::chrono::duration<double> getTime();
        void restartTime();
        void printTime();
        ~Clock();

    protected:
    private:
        std::chrono::time_point<std::chrono::system_clock> start;
};