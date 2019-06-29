//
// EPITECH PROJECT, 2019
// OOP_indie_studio_2018
// File description:
// explosion
//

#include "explosion.hpp"

Explosion::Explosion(IrrlichtDevice *device, ISceneManager *s, IVideoDriver *d, ISceneNode *n, int r = 1) : _radius(r), _smgr(s), _driver(d)
{
    if (!_smgr)
        std::cerr << "Scene Manager loading failed" << std::endl;
    ISceneNode *node = n;
    _psv = _smgr->addParticleSystemSceneNode(false);
    _psh = _smgr->addParticleSystemSceneNode(false);
    _emv = _psv->createBoxEmitter(
            node->getBoundingBox(), // emitter size
            core::vector3df(0.0f,0.06f,0.0f),   // initial direction
            300,400,                             // emit rate
            video::SColor(0,255,255,255),       // darkest color
            video::SColor(0,255,255,255),       // brightest color
            800,2000,20,                         // min and max age, angle
            core::dimension2df(70.5f,70.5f),         // min size
            core::dimension2df(70.5f,90.5f));
    _emh = _psh->createBoxEmitter(
            node->getBoundingBox(), // emitter size
            core::vector3df(0.0f,0.06f,0.0f),   // initial direction
            300,400,                             // emit rate
            video::SColor(0,255,255,255),       // darkest color
            video::SColor(0,255,255,255),       // brightest color
            800,2000,20,                         // min and max age, angle
            core::dimension2df(70.5f,70.5f),         // min size
            core::dimension2df(70.5f,90.5f));
    this->explode(device, node);
}

Explosion::~Explosion()
{
}

void Explosion::explode(IrrlichtDevice *device, ISceneNode *node)
{
    _psv->setEmitter(_emv); // this grabs the emitter
    _psh->setEmitter(_emh);
    _emv->drop(); // so we can drop it here without deleting it
    _emh->drop();

    scene::IParticleAffector* pafv = _psv->createFadeOutParticleAffector();
    scene::IParticleAffector* pafh = _psh->createFadeOutParticleAffector();
    _psv->addAffector(pafv); // same goes for the affector
    _psh->addAffector(pafh);
    pafv->drop();
    pafh->drop();

    _psv->setPosition(node->getPosition());
    _psh->setPosition(node->getPosition());
    _psv->setScale(core::vector3df(1, 1, 1));
    _psh->setScale(core::vector3df(1, 1, 1));
    _psv->setMaterialFlag(video::EMF_LIGHTING, true);
    _psh->setMaterialFlag(video::EMF_LIGHTING, true);
    _psv->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
    _psh->setMaterialFlag(video::EMF_ZWRITE_ENABLE, true);
    _psv->setMaterialTexture(0, _driver->getTexture("media/fireball.bmp"));
    _psh->setMaterialTexture(0, _driver->getTexture("media/fireball.bmp"));
    _psv->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    _psh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    _smgr->drawAll();
    _psv->setScale(core::vector3df(3 + _radius - 1, 1, 1));
    _psh->setScale(core::vector3df(1, 1, 3 + _radius - 1));
    _psv->clearParticles();
    _psh->clearParticles();
    _smgr->addToDeletionQueue(node);//3 + _radius - 1
}

void Explosion::clear()
{
    //_psv->removeAllAffectors();;
    //_psh->removeAllAffectors();
    _smgr->addToDeletionQueue(_psh);
    _smgr->addToDeletionQueue(_psv);
    //_psv->drop();
    //_psh->drop();
}

void Explosion::setExplosion()
{
}