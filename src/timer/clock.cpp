//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// clock
//

#include "clock.hpp"

Clock::Clock() : _clock(std::chrono::steady_clock::now())
{
}

Clock::~Clock()
{
}

Time Clock::getDeltaTime()
{
    auto end(std::chrono::steady_clock::now());
    Time delta(end - _clock);
    return (delta);
}

Time Clock::restart()
{
    auto end(std::chrono::steady_clock::now());
    Time delta(end - _clock);

    _clock = std::chrono::steady_clock::now();
    return (delta);
}