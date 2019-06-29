//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// time
//

#include "time.hpp"

Time::Time(std::chrono::nanoseconds ns) : _time(ns)
{
}

Time::Time(std::chrono::milliseconds ms) : _time(ms)
{
}

Time::Time(std::chrono::seconds s) : _time(s)
{
}

Time &Time::operator=(std::chrono::nanoseconds ns)
{
    _time = ns;
}

Time &Time::operator=(std::chrono::milliseconds ms)
{
    _time = ms;
}

Time &Time::operator=(std::chrono::seconds s)
{
    _time = s;
}

long int Time::getNanosecond()
{
    return (_time.count());
}

long int Time::getMillisecond()
{
    return (std::chrono::duration_cast<std::chrono::milliseconds>(_time).count());
}

long int Time::getSecond()
{
    return (std::chrono::duration_cast<std::chrono::seconds>(_time).count());
}