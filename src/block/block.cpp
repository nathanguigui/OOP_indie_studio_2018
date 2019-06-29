/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** block
*/

#include "block.hpp"

DestructiveBlock::DestructiveBlock(vector2df _pos, ISceneManager *smgr, IVideoDriver *driver)
    : _driver(driver), _smgr(smgr), _isDestr(true) {
    _positions = _pos;
    _block = _smgr->addCubeSceneNode(255.f, 0, -1);
    _block->setPosition(vector3df(_pos.X, 0.f, _pos.Y));
    _block->setMaterialFlag(video::EMF_LIGHTING, false);
    _block->setMaterialTexture(0, driver->getTexture("media/block/planks_oak.png"));
    _block->setScale(vector3df(1, 1, 1));
}

DestructiveBlock::~DestructiveBlock() {

}

ISceneNode* DestructiveBlock::getNode()
{
    return _block;
}

vector3df DestructiveBlock::getPosition() {
    vector3df pos(_positions.X, 0, _positions.Y);
    return pos;
}

void DestructiveBlock::explosion() {
    IParticleSystemSceneNode* ps = _smgr->addParticleSystemSceneNode(false);
    IParticleEmitter* em = ps->createBoxEmitter(
            _block->getBoundingBox(),           // emitter size
            core::vector3df(0.0f,0.06f,0.0f),   // initial direction
            200,300,                             // emit rate
            video::SColor(0,255,255,255),       // darkest color
            video::SColor(0,255,255,255),       // brightest color
            800,2000,0,                         // min and max age, angle
            core::dimension2df(50.5f,50.5f),         // min size
            core::dimension2df(50.5f,50.5f));         // max size

    ps->setEmitter(em); // this grabs the emitter
    em->drop(); // so we can drop it here without deleting it

    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf); // same goes for the affector
    paf->drop();

    ps->setPosition(_block->getPosition());
    ps->setScale(core::vector3df(1,1,1));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, _driver->getTexture("media/fire.bmp"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

IndestructibleBlock::IndestructibleBlock(vector2df _pos, ISceneManager *smgr, IVideoDriver *driver)
    : _driver(driver), _smgr(smgr), _isDestr(false) {
    _block = _smgr->addCubeSceneNode(255.f, 0, -1);
    _block->setPosition(vector3df(_pos.X, 0.f, _pos.Y));
    _block->setMaterialFlag(video::EMF_LIGHTING, false);
    _block->setMaterialTexture(0, driver->getTexture("media/cobblestone.png"));
    _block->setScale(vector3df(1, 1, 1));
}

IndestructibleBlock::~IndestructibleBlock() {

}

ISceneNode* IndestructibleBlock::getNode()
{
    return _block;
}

vector3df IndestructibleBlock::getPosition() {
    return _block->getPosition();
}

void explodeThisBlock(DestructiveBlock *block) {
    block->explosion();
}