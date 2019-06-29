/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** launcher
*/

#ifndef LAUNCHER_HPP_
#define LAUNCHER_HPP_

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

#include "menu.hpp"
#include "settings.hpp"
#include "SFML/Audio.hpp"

class BombermanLauncher {
public:
    BombermanLauncher(bool value);
    ~BombermanLauncher();
    IVideoDriver *_driver;
    ISceneManager *_smgr;
    IGUIEnvironment *_gui;
    IrrlichtDevice *_device;
    MyMenu *getMainMenu();
    void addPlayer(BombermanSettings *settings, int);
    void remPlayer(BombermanSettings *settings);
    bool startGame(BombermanSettings *settings);
    void setOstVolume(int volume);
    sf::Music _ost;
private:
    MyMenu *main_menu;
};

BombermanSettings *start_launcher();

#endif /* !LAUNCHER_HPP_ */
