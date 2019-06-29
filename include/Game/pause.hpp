/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** pause.hpp
*/
#ifndef OOP_INDIE_STUDIO_2018_PAUSE_HPP
#define OOP_INDIE_STUDIO_2018_PAUSE_HPP

#include "irrlicht/irrlicht.h"
#include "EventReceiver.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class PauseMenu {
public:
    PauseMenu(IGUIEnvironment *gui, IrrlichtDevice *device);
    void draw();
    void remove();
    ~PauseMenu() = default;
private:
    IGUIButton *_resume;
    IGUIButton *_exit;
};

#endif //OOP_INDIE_STUDIO_2018_PAUSE_HPP
