/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** settings
*/

#include "settings.hpp"

BombermanSettings::BombermanSettings()
{
    _gameStarted = false;
    _splashscreen = true;
    _map_size = 1;
    _sound = 100;
    _music = 100;
    _map_size = 1;
}

void BombermanSettings::set_splashscreen(bool value)
{
    _splashscreen = value;
}

void BombermanSettings::set_volume(s32 sound, s32 music)
{
    _sound = sound;
    _music = music;
}

std::vector<Figure*> BombermanSettings::getPlayerList() const
{
    return _playerList;
}

int BombermanSettings::getPlayerCount()
{
    return _playerList.size();
}

bool BombermanSettings::addPlayer(std::string name, int skin, int player_nb)
{
    std::cout << skin;
    if (this->getPlayerCount() == 4)
        return false;
    Figure *fig = new Figure(name, skin, player_nb);
    _playerList.push_back(fig);
    return true;
}

bool BombermanSettings::startGame()
{
    if (this->getPlayerCount() == 0)
        return false;
    _gameStarted = true;
    return true;
}

bool BombermanSettings::isGameStarted()
{
    return _gameStarted;
}

BombermanSettings::~BombermanSettings() {}

void BombermanSettings::setMapSize(int size)
{
    _map_size = size;
}

int BombermanSettings::getMapSize() {
    return _map_size;
}

bool BombermanSettings::doSplashscreen() {
    return _splashscreen;
}

int BombermanSettings::get_map_size() {
    return (map_size);
}

void BombermanSettings::set_map_size(int c) {
    if (c == 0 || c == 1 || c == 2)
        map_size = c + 1;
}
