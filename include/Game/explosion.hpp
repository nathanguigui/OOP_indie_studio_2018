//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// explosion
//

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "irrlicht/irrlicht.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

enum class AXE
{
    HORIZONTAL,
    VERTICAL
};

class Explosion
{
public:
    Explosion(IrrlichtDevice *, ISceneManager *, IVideoDriver *, ISceneNode *, int);
    ~Explosion();
    void explode(IrrlichtDevice *, ISceneNode *);
    void clear();
    void setExplosion();
private:
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    IParticleSystemSceneNode *_psv;
    IParticleSystemSceneNode *_psh;
    IParticleEmitter *_emv;
    IParticleEmitter *_emh;
    int _radius;
};
#endif /* !EXPLOSION_HPP_ */
