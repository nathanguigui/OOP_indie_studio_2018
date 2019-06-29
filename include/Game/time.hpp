//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// time
//

#ifndef TIME_HPP
#define TIME_HPP_

#include <chrono>

class Time
{
public:
    Time(std::chrono::nanoseconds ns);
    Time(std::chrono::milliseconds ms);
    Time(std::chrono::seconds s);
    Time &operator=(std::chrono::nanoseconds ns);
    Time &operator=(std::chrono::milliseconds ms);
    Time &operator=(std::chrono::seconds s);
    long int getSecond();
    long int getMillisecond();
    long int getNanosecond();
private:
    std::chrono::nanoseconds _time;
};

#endif /* !TIME_HPP_ */
