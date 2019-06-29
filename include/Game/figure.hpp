/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** figure.hpp
*/

#ifndef OOP_INDIE_STUDIO_2018_FIGURE_HPP
#define OOP_INDIE_STUDIO_2018_FIGURE_HPP
#include "irrlicht/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

#include <iostream>
#include <cstring>

class Figure {
public:
    Figure(std::string, int, int);
    ~Figure() = default;
    size_t getBomb() const;
    size_t getFire() const;
    size_t getSpeed() const;
    size_t getLives() const;
    EKEY_CODE *getKeyBindings();
    std::string getName();
    ITexture *getTexture(IVideoDriver *driver);
private:
    int _skin_id;
    size_t _bomb;
    size_t _fire;
    size_t _speed;
    size_t _lives;
    irr::EKEY_CODE _keyBindings[5];
    std::string _name;
};

#endif //OOP_INDIE_STUDIO_2018_FIGURE_HPP
