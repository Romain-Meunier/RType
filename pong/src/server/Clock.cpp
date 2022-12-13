/*
** EPITECH PROJECT, 2022
** Clock.cpp
** File description:
** Clock.cpp
*/

#include "Clock.hpp"

Clock::Clock()
{
    start = std::chrono::system_clock::now();
}

std::chrono::duration<double> Clock::getTime() 
{
    return(std::chrono::system_clock::now() - start);
}

void Clock::restartTime() 
{
    start = std::chrono::system_clock::now();
}

void Clock::printTime() 
{
    std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - start;
    std::cout << elapsed_time.count() << std::endl;
}

Clock::~Clock()
{
}