/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** overlay
*/

#ifndef OVERLAY_HPP_
#define OVERLAY_HPP_


#include "irrlicht/irrlicht.h"
#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
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

#include "BomberPlayer.hpp"
using namespace Gameplay;

class ScoreOverlay {
public:
    ScoreOverlay(IGUIEnvironment *env, IrrlichtDevice *device, std::string &name, int playerNB, time_t time, int def_score = 250);
    ~ScoreOverlay() = default;
    void update();
    void pause(int delta_s);
private:
    std::string _name;
    int _score;
    int _def_score;
    time_t _start;
    IGUIStaticText *_overlay_name;
};

class PlayerOverlay {
public:
    PlayerOverlay(IGUIEnvironment *gui, ISceneManager *smgr, IPlayer *player, std::string &name);
    ~PlayerOverlay() = default;
    void update();
    void setLives(int lives);
private:
    std::string _name;
    IPlayer *_player;
    int _lives;
    ITextSceneNode *_overlay_lives;

};

class Overlay {
public:
    Overlay(IGUIEnvironment *env, ISceneManager *smgr, IrrlichtDevice *device, int time_limit = 600, int def_score = 250);
    ~Overlay() = default;
    void updateOverlay();
    const wchar_t *getTime();
    bool addScoreOverlay(std::string name, int playerNB);
    bool addPlayerOverlay(IPlayer *player, std::string name);
    void pauseOverlay();
private:
    std::vector<ScoreOverlay*> _players_score;
    std::vector<PlayerOverlay*> _players_overlay;
    int _def_score;
    int _time_limit;
    int _time_left;
    time_t _start;
    IGUIEnvironment *_env;
    IGUIStaticText *_timer;
    IrrlichtDevice *_device;
    IGUIFont *_font;
    ISceneManager *_smgr;
};

#endif