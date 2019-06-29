/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <vector>
#include "irrlicht/irrlicht.h"
#include "block.hpp"
#include "BomberPlayer.hpp"
#include "IPlayer.hpp"
#include "generator.hpp"
#include <thread>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace Gameplay;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class GameMap {
    public:
        GameMap(video::IVideoDriver *driver, scene::ISceneManager *smgr, int size);
        static vector3df getPos(vector3df coords);
        static vector3df getCoords(vector3df coords);
        static vector3df positionForBomb(vector3df pos);
        void setCollision(IPlayer*);
        void explodeWall(vector3df pos, int radius);
        vector3df getSpawnPoint(int i);
        std::vector<std::string> getMap();
        ICameraSceneNode *getCamera();
        vector2df getSize() const { return _size; };
        ~GameMap() = default;
    private:
        void fillMap(std::vector<std::string> map);
        void addSpawnPoint(vector3df pos);
        void removeBlock(vector2di tab, std::vector<DestructiveBlock*>::iterator block_it);
        vector2df _size;
        ISceneManager *_smgr;
        IVideoDriver *_driver;
        ICameraSceneNode *_camera;
        std::vector<std::string> _map;
        std::vector<DestructiveBlock*> _destructive_blocks;
        std::vector<IndestructibleBlock*> _blocks;
        std::vector<IGameBlock*> _all_blocks;
        std::vector<vector3df> _spawn_points;
        std::vector<IPlayer*> _all_players;
};

#endif /* !MAP_HPP_ */
