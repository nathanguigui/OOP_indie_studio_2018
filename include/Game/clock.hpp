//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// clock
//

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "time.hpp"

class Clock
{
public:
    Clock();
    ~Clock();
    Time getDeltaTime();
    Time restart();
private:
    std::chrono::time_point<std::chrono::steady_clock> _clock;
};

#endif /* !CLOCK_HPP_ */