/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** map
*/

#include "map.hpp"

GameMap::GameMap(IVideoDriver *driver, ISceneManager *smgr, int i) : _smgr(smgr), _driver(driver)
{
    _camera = smgr->addCameraSceneNode(0);
    if (i == 1) {
        _camera->setPosition(core::vector3df(4681.9, 2392.38, 2034.71));
        _camera->setTarget(core::vector3df(827.443, -1721.25, 2104.79));
        _size.X = 16;
        _size.Y = 16;
    } else if (i == 2) {
        _camera->setPosition(core::vector3df(9214.5, 4821.79, 3596.11));
        _camera->setTarget(core::vector3df(1286.53, -2885.52, 3747.73));
        _size.X = 32;
        _size.Y = 32;
    } else if (i == 3) {
        _camera->setPosition(core::vector3df(5604, 8456.19, 5942.02));
        _camera->setTarget(core::vector3df(6014.23, -3293.33, 5949.57));
        _size.X = 64;
        _size.Y = 64;
    }
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    _camera->setFarValue(42000.0f);
    _smgr->setAmbientLight(video::SColor(0,60,60,60));
    _map = generation(i);
    fillMap(_map);
}

vector3df GameMap::getPos(vector3df coords)
{
    vector3df pos;
    pos.X = round(coords.X * 255);
    pos.Y = round(coords.Y * 255);
    pos.Z = round(coords.Z * 255);
    return pos;
}

vector3df GameMap::getCoords(vector3df pos)
{
    vector3df coords;
    coords.X = round(pos.X / 255);
    coords.Y = round(pos.Y / 255);
    coords.Z = round(pos.Z / 255);
    return coords;
}

vector3df GameMap::positionForBomb(vector3df pos)
{
    return getPos(getCoords(pos));
}

void GameMap::fillMap(std::vector<std::string> map)
{
    for (int i = 0; i < map.size(); i ++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '2') {
                DestructiveBlock *block = new DestructiveBlock(vector2df(i * 255.f, j * 255.f), _smgr, _driver);
                _destructive_blocks.push_back(block);
                _all_blocks.push_back((IGameBlock*)block);
            } if (map[i][j] == '1') {
                IndestructibleBlock *block = new IndestructibleBlock(vector2df(i * 255.f, j * 255.f), _smgr, _driver);
                _blocks.push_back(block);
                _all_blocks.push_back((IGameBlock*)block);
            } if (map[i][j] == '4')
                addSpawnPoint(vector3df(i*255.f, 0, j*255.f));
        }
    }
}

void GameMap::setCollision(IPlayer *player)
{
    _all_players.push_back(player);
    for (int i = 0; i < _destructive_blocks.size(); i++) {
        ITriangleSelector *selector = _smgr->createTriangleSelectorFromBoundingBox(_destructive_blocks[i]->getNode());
        _destructive_blocks[i]->getNode()->setTriangleSelector(selector);
        ISceneNodeAnimator *anim = _smgr->createCollisionResponseAnimator(selector, player->getSceneNode(),
                core::vector3df(30,50,30), core::vector3df(0,0,0), core::vector3df(0,30,0));
        selector->drop();
        player->getSceneNode()->addAnimator(anim);
        anim->drop();
    } for (int i = 0; i < _blocks.size(); i++) {
        ITriangleSelector *selector = _smgr->createTriangleSelectorFromBoundingBox(_blocks[i]->getNode());
        _blocks[i]->getNode()->setTriangleSelector(selector);
        ISceneNodeAnimator *anim = _smgr->createCollisionResponseAnimator(selector, player->getSceneNode(),
                core::vector3df(30,50,30), core::vector3df(0,0,0), core::vector3df(0,30,0));
        selector->drop();
        player->getSceneNode()->addAnimator(anim);
        anim->drop();
    }
}

void GameMap::explodeWall(vector3df pos, int radius)
{
    vector3df coords = GameMap::getCoords(pos);

    for (int i = 1; i <= radius; i++) {
        if (_map[coords.X][coords.Z + i] == '1' || _map[coords.X][coords.Z+i] == '2') {
            if (_map[coords.X][coords.Z + i] == '2') {
                for (std::vector<DestructiveBlock*>::iterator it = _destructive_blocks.begin(); it < _destructive_blocks.end(); it++) {
                    DestructiveBlock *tmp = *it;
                    if (tmp->getPosition().X == coords.X*255 && tmp->getPosition().Z == (coords.Z+i)*255)
                        removeBlock(vector2di(coords.X, coords.Z+i), it);
                }
            }
            break;
        }
    } for (int i = 1; i <= radius; i++) {
        if (_map[coords.X][coords.Z-i] == '1' || _map[coords.X][coords.Z-i] == '2') {
            if (_map[coords.X][coords.Z-i] == '2') {
                for (std::vector<DestructiveBlock*>::iterator it = _destructive_blocks.begin(); it < _destructive_blocks.end(); it++) {
                    DestructiveBlock *tmp = *it;
                    if (tmp->getPosition().X == coords.X*255 && tmp->getPosition().Z == (coords.Z-i)*255)
                        removeBlock(vector2di(coords.X, coords.Z-i), it);
                }
            }
            break;
        }
    } for (int i = 1; i <= radius; i++) {
        if (_map[coords.X+i][coords.Z] == '1' || _map[coords.X+i][coords.Z] == '2') {
            if (_map[coords.X+i][coords.Z] == '2') {
                for (std::vector<DestructiveBlock*>::iterator it = _destructive_blocks.begin(); it < _destructive_blocks.end(); it++) {
                    DestructiveBlock *tmp = *it;
                    if (tmp->getPosition().Z == coords.Z*255 && tmp->getPosition().X == (coords.X+i)*255)
                        removeBlock(vector2di(coords.X+i, coords.Z), it);
                }
            }
            break;
        }
    } for (int i = 1; i <= radius; i++) {
        if (_map[coords.X-i][coords.Z] == '1' || _map[coords.X - i][coords.Z] == '2') {
            if (_map[coords.X-i][coords.Z] == '2') {
                for (std::vector<DestructiveBlock*>::iterator it = _destructive_blocks.begin(); it < _destructive_blocks.end(); it++) {
                    DestructiveBlock *tmp = *it;
                    if (tmp->getPosition().Z == coords.Z*255 && tmp->getPosition().X == (coords.X-i)*255)
                        removeBlock(vector2di(coords.X-i, coords.Z), it);
                }
            }
            break;
        }
    }
}

void GameMap::removeBlock(vector2di tab, std::vector<DestructiveBlock*>::iterator block_it) {
    _map[tab.X][tab.Y] = '0';
    DestructiveBlock *block = *block_it;
    vector3df pos = block->getNode()->getPosition();
    block->getNode()->setPosition(vector3df(pos.X, pos.Y+5000, pos.Z));
}

std::vector<std::string> GameMap::getMap() {
    return _map;
}

void GameMap::addSpawnPoint(vector3df pos) {
    if (_spawn_points.size() != 4)
        _spawn_points.push_back(pos);
}

vector3df GameMap::getSpawnPoint(int i) {
    if (_spawn_points.size() - 1 < i)
        return vector3df(0,0,0);
    return _spawn_points[i];
}

ICameraSceneNode *GameMap::getCamera()
{
    return _camera;
}

