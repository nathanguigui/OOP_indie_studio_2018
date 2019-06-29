/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IPowerUp
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "IPlayer.hpp"

using namespace irr;
using namespace core;
using namespace video;

namespace Gameplay {

    class PowerUp {
    	public:
            PowerUp(E_PLAYER_PICKUP value, vector2df t_pos, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device);
    		~PowerUp();
            E_PLAYER_PICKUP getPower() const { return m_power; };
            irr::core::vector2df getPosition() const { return m_pos; };

    	protected:
            const E_PLAYER_PICKUP m_power;
            const vector2df m_pos;
            ISceneManager *m_smgr;
            IVideoDriver *m_driver;
            ISceneNode *m_node;
    };
}

