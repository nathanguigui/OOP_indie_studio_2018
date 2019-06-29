/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** block
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "irrlicht/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <thread>

class IGameBlock {
    public:
        virtual ~IGameBlock() = default;
        virtual vector3df getPosition() = 0;
        virtual ISceneNode *getNode() = 0;
        virtual const bool isDestructible() const = 0;
};

class DestructiveBlock : IGameBlock {
public:
    DestructiveBlock(vector2df _pos, ISceneManager *smgr, IVideoDriver *driver);
    vector3df getPosition() final;
    void explosion();
    ISceneNode *getNode() final;
    const bool isDestructible() const { return _isDestr; };
    ~DestructiveBlock() final;
private:
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    ISceneNode *_block;
    vector2df _positions;
    const bool _isDestr;
};

class IndestructibleBlock : IGameBlock {
public:
    IndestructibleBlock(vector2df _pos, ISceneManager *smgr, IVideoDriver *driver);
    vector3df getPosition() final;
    ~IndestructibleBlock() final;
    ISceneNode *getNode() final;
    const bool isDestructible() const { return _isDestr; };
private:
    ISceneManager *_smgr;
    IVideoDriver *_driver;
    ISceneNode *_block;
    const bool _isDestr;
};

void explodeThisBlock(DestructiveBlock *block);
#endif /* !BLOCK_HPP_ */
