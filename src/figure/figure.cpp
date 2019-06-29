/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** figure.cpp
*/

#include "figure.hpp"

Figure::Figure(std::string name, int skin, int player_nb) : _name(name), _skin_id(skin)
{
    EKEY_CODE tmp[5];
    switch (player_nb) {
        case 0:
            tmp[1] = KEY_KEY_Z;
            tmp[3] = KEY_KEY_Q;
            tmp[0] = KEY_KEY_S;
            tmp[2] = KEY_KEY_D;
            tmp[4] = KEY_SPACE;
            break;
        case 1:
            tmp[1] = KEY_UP;
            tmp[3] = KEY_LEFT;
            tmp[0] = KEY_DOWN;
            tmp[2] = KEY_RIGHT;
            tmp[4] = KEY_CONTROL;
            break;
        case 2:
            tmp[1] = KEY_KEY_O;
            tmp[3] = KEY_KEY_K;
            tmp[0] = KEY_KEY_L;
            tmp[2] = KEY_KEY_M;
            tmp[4] = KEY_KEY_P;
            break;
        case 3:
            tmp[1] = KEY_KEY_T;
            tmp[3] = KEY_KEY_F;
            tmp[0] = KEY_KEY_G;
            tmp[2] = KEY_KEY_H;
            tmp[4] = KEY_KEY_Y;
            break;
        default:
            break;
    }
    std::memcpy(_keyBindings, tmp, sizeof(EKEY_CODE) * 5);
    _bomb = 1;
    _fire = 1;
    _speed = 1;
    _lives = 1;
}

size_t Figure::getBomb() const {
    return _bomb;
}

size_t Figure::getFire() const {
    return _fire;
}

size_t Figure::getSpeed() const {
    return _speed;
}

size_t Figure::getLives() const {
    return _lives;
}

EKEY_CODE *Figure::getKeyBindings() {
    return _keyBindings;
}

std::string Figure::getName(){
    return _name;
}

ITexture *Figure::getTexture(IVideoDriver *driver) {
    std::cout << _skin_id;
    switch (_skin_id) {
        case 1:
            return driver->getTexture("media/colors/red.png");
        case 2:
            return driver->getTexture("media/colors/green.png");
        case 3:
            return driver->getTexture("media/colors/yellow.png");
        case 4:
            return driver->getTexture("media/colors/blue.png");
        default:
            return driver->getTexture("media/colors/blue.png");
    }
}
