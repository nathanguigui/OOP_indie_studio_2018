//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// IBomb
//

#pragma once

#include "irrlicht/irrlicht.h"

enum class DIR
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class IBomb
{
public:
    virtual ~IBomb() {};
    virtual irr::core::vector3df getPosition() = 0;
    virtual int getRadius() = 0;
    //virtual void Move(DIR) = 0;
    virtual void loadExplosion(irr::IrrlichtDevice *) = 0;
};