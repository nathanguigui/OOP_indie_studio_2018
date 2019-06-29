/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <iostream>
#include <vector>
#include "irrlicht/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "figure.hpp"

class BombermanSettings {
public:
    BombermanSettings();
    ~BombermanSettings();
    int getPlayerCount();
    std::vector<Figure*> getPlayerList() const;
    bool addPlayer(std::string, int, int);
    bool startGame();
    bool isGameStarted();
    void setMapSize(int size);
    int getMapSize();
    bool doSplashscreen();
    void set_splashscreen(bool value);
    void set_volume(s32, s32);
    void set_map_size(int);
    int get_map_size();
    s32 get_sound(void) const {return _sound;}
    s32 get_music(void) const {return _music;}
    bool get_splashscreen(void) const {return _splashscreen;}
    std::string get_name(void) const {return _playerList[0]->getName();}
private:
    int map_size;
    s32 _sound;
    s32 _music;
    bool _gameStarted;
    int _map_size;
    bool _splashscreen;
    std::vector<Figure*> _playerList;
};

#endif /* !SETTINGS_HPP_ */
