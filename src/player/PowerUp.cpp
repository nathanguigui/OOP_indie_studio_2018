/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PowerUp
*/

#include "PowerUp.hpp"

using namespace Gameplay;

PowerUp::PowerUp(E_PLAYER_PICKUP value, vector2df t_pos, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device)
    : m_power(value), m_pos(t_pos), m_smgr(smgr), m_driver(driver) {
    
    /* CREATE NODE AND ADD TEXTURE TO POWERUP
    
    m_node = _smgr->addSphereSceneNode(127.5f);
    m_node->setPosition(vector3df(_pos.X, 0.f, _pos.Y));
    m_node->setMaterialFlag(video::EMF_LIGHTING, true);
    
    switch (value) {
        case EPI_BOMB:
            m_node->setMaterialTexture(0, _driver->getTexture("media/bomb.png")); // set appropriate texture here
            break;
        case EPI_FIRE:
            m_node->setMaterialTexture(0, _driver->getTexture("media/bomb.png")); // set appropriate texture here
            break;
        case EPI_SPEED:
            m_node->setMaterialTexture(0, _driver->getTexture("media/bomb.png")); // set appropriate texture here
            break;
    }

    */
}

PowerUp::~PowerUp() {}
