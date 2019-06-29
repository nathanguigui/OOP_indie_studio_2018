/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "irrlicht/irrlicht.h"
#include "IBomb.hpp"
#include "explosion.hpp"
#include <iostream>
#include <thread>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

enum STATE {
    NORMAL,
    EXPLOSE,
    ERASE
};

class Bomb : public IBomb {
    public:
        Bomb(vector3df pos, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device, int radius);
        Bomb(vector3df pos, IrrlichtDevice *device, int radius);
        ~Bomb();

        // getter
        vector3df getPosition();
        int getRadius();
        STATE getState();
        ISceneManager *getSmgr();
        IVideoDriver *getDriver();
        ISceneNode *getNode();
        u32 getStartTime();
        u32 getCurrentTime();
        u32 getDeltaTime();

        // setter
        void setState(STATE);
        void loadTexture();
        void setCurrentTime(time_t);

        void explodeIt();
        bool hasEnd();
        bool isExplosing();
        void loadExplosion(IrrlichtDevice *device);
        void clearExplosion();
        bool stateEffect(IrrlichtDevice *device);
    private:
        int _radius;
        ISceneManager *_smgr;
        IVideoDriver *_driver;
        ISceneNode *_bomb;
        Explosion *explosion;
        STATE _state;
        time_t _now;
        bool explode;
        ITimer *_t;

        u32 _start;
        //IParticleSystemSceneNode *_explosion;
        IParticleSystemSceneNode *psX;
        IParticleSystemSceneNode *psY;
        void explosionX();
        void explosionY();
};

#endif /* !BOMB_HPP_ */
