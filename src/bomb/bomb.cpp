/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** bomb
*/

#include "bomb.hpp"
#include "map.hpp"


Bomb::Bomb(vector3df pos, ISceneManager *smgr, IVideoDriver *driver, IrrlichtDevice *device, int radius = 1) : _driver(driver), _smgr(smgr), _radius(radius)
{
    _t = device->getTimer();
    _start = _t->getTime();
    _state = STATE::NORMAL;
    _start = time(0);
    _bomb = _smgr->addSphereSceneNode(127.5f);
    _bomb->setPosition(GameMap::positionForBomb(pos));
    _bomb->setMaterialFlag(video::EMF_LIGHTING, true);
    _bomb->setMaterialTexture(0, _driver->getTexture("media/bomb.png"));
    _smgr->drawAll();
    explode = false;
}

Bomb::Bomb(vector3df pos, IrrlichtDevice *device, int radius = 1) : _radius(radius)
{
    _t = device->getTimer();
    _start = _t->getTime();
    _smgr = device->getSceneManager();
    _driver = device->getVideoDriver();
    _state = STATE::NORMAL;
    _now = time(0);
    _bomb = _smgr->addSphereSceneNode(127.5f);
    _bomb->setPosition(GameMap::positionForBomb(pos));
    _bomb->setMaterialFlag(video::EMF_LIGHTING, true);
    _bomb->setMaterialTexture(0, _driver->getTexture("media/bomb.png"));
    _smgr->drawAll();
    explode = false;
}

Bomb::~Bomb()
{
    _bomb->remove();
    psX->remove();
    psY->remove();
}

bool Bomb::hasEnd()
{
    u32 delta = getDeltaTime();
    return (delta > 3000);
}

u32 Bomb::getDeltaTime()
{
    u32 now = _t->getTime();
    return (now - _start);
}

void Bomb::explodeIt()
{
    if (!explode) {
    explosionX();
    explosionY();
    _bomb->setVisible(false);
    explode = true;
    }
}

void Bomb::explosionX()
{
    psX = _smgr->addParticleSystemSceneNode(false);
    IParticleEmitter *emX = psX->createBoxEmitter(
            _bomb->getBoundingBox(), // emitter size
            core::vector3df(0.0f,0.06f,0.0f),   // initial direction
            300,400,                             // emit rate
            video::SColor(0,255,255,255),       // darkest color
            video::SColor(0,255,255,255),       // brightest color
            800,2000,20,                         // min and max age, angle
            core::dimension2df(70.5f,70.5f),         // min size
            core::dimension2df(70.5f,90.5f));
    psX->setEmitter(emX);
    emX->drop();
    psX->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    psX->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    psX->setMaterialTexture(0, _driver->getTexture("media/fireball.bmp"));
    psX->setScale(core::vector3df(3 + _radius - 1, 1, 1));
    psX->setPosition(getPosition());
}

void Bomb::explosionY()
{
    psY = _smgr->addParticleSystemSceneNode(false);
    IParticleEmitter *emY = psY->createBoxEmitter(
            _bomb->getBoundingBox(), // emitter size
            core::vector3df(0.0f,0.06f,0.0f),   // initial direction
            300,400,                             // emit rate
            video::SColor(0,255,255,255),       // darkest color
            video::SColor(0,255,255,255),       // brightest color
            1,2000,20,                         // min and max age, angle
            core::dimension2df(70.5f,70.5f),         // min size
            core::dimension2df(70.5f,90.5f));
    psY->setEmitter(emY);
    emY->drop();
    psY->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    psY->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    psY->setMaterialTexture(0, _driver->getTexture("media/fireball.bmp"));
    psY->setScale(core::vector3df(1, 1,3 + _radius - 1));
    psY->setPosition(getPosition());
}

vector3df Bomb::getPosition()
{
    return _bomb->getAbsolutePosition();
}

int Bomb::getRadius()
{
    return (_radius);
}

ISceneManager *Bomb::getSmgr()
{
    return (_smgr);
}

STATE Bomb::getState()
{
    return (_state);
}

IVideoDriver *Bomb::getDriver()
{
    return (_driver);
}

ISceneNode *Bomb::getNode()
{
    return (_bomb);
}

void Bomb::setState(STATE state)
{
    _state = state;
}

bool Bomb::isExplosing()
{
    return (_state == STATE::EXPLOSE);
}

u32 Bomb::getStartTime()
{
    return (_start);
}

u32 Bomb::getCurrentTime()
{
    return (_t->getTime());
}

void Bomb::loadTexture()
{
    io::path path[4] = {
                            "media/bomb.png",
                            "media/yellow.png",
                            "media/orange.png",
                            "media/red.png"
                        };
    int idx = ((_state == STATE::NORMAL)? 0 : 3);
    _bomb->setMaterialTexture(idx, _driver->getTexture(path[idx]));
    _smgr->drawAll();
}

void Bomb::setCurrentTime(time_t now)
{
    _now = now;
}

void Bomb::loadExplosion(IrrlichtDevice *device)
{
    explosion = new Explosion(device, _smgr, _driver, _bomb, _radius);
    explode = true;
    _state = STATE::EXPLOSE;
}

void Bomb::clearExplosion()
{
    if (_driver && _smgr && _bomb) {
        explosion->clear();
        explosion = 0;
        _state = STATE::ERASE;
    }
}

bool Bomb::stateEffect(IrrlichtDevice *device)
{
    if (_state == ERASE)
        return false;
        if (_t->getTime() - _start > 1000)  {
            loadExplosion(device);
            return true;
        }
}