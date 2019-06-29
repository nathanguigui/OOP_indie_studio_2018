/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "irrlicht/irrlicht.h"
#include <iostream>
#include "BomberPlayer.hpp"
#include "explosion.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "generator.hpp"
#include <sstream>
#include <iomanip>
#include <vector>
#include "BomberAI.hpp"
#include "overlay.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace Gameplay;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "SFML/Audio.hpp"
#include "pause.hpp"
class Overlay;

class BombermanGame {
    public:
        BombermanGame(EventReceiver receive, BombermanSettings *settings);
        void pollAllEvents();
        void play();
        void pause();
        void unpause();
        void splashScreen();
        bool run();
        std::vector<IPlayer*> getPlayers() { return _players; };
        ~BombermanGame();
        EventReceiver _receiver;
        IVideoDriver *_driver;
        ISceneManager *_smgr;
        gui::IGUIEnvironment *_gui;
        IrrlichtDevice *_device;
        std::vector<IPlayer*> _players;
        BombermanSettings *_settings;
        GameMap *_map;
        Overlay *_overlay;
        bool _paused;
        int rip;
        sf::Music _splash_sound;
        PauseMenu *_menu;
};

void start_game(BombermanSettings *settings);
#endif /* !GAME_HPP_ */