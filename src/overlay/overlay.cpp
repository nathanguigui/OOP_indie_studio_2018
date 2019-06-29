/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** overlay
*/

#include "overlay.hpp"

Overlay::Overlay(IGUIEnvironment *env, ISceneManager *smgr, IrrlichtDevice *device, int time_limit, int def_score) :
        _time_limit(time_limit), _def_score(def_score), _env(env), _device(device), _smgr(smgr) {
    _start = time(nullptr);
    _font = _env->getFont("media/font/myfont.xml");
    _env->getSkin()->setFont(_font);
    _timer = _env->addStaticText(getTime(), rect<s32>(0, 0, _device->getVideoModeList()->getDesktopResolution().Width, 100));
    _timer->setTextAlignment(EGUIA_CENTER, EGUIA_UPPERLEFT);
    _timer->setOverrideColor(SColor(255,255,255,255));
    _time_left = _time_limit;
}

void Overlay::updateOverlay() {
    _timer->setText(getTime());
    ScoreOverlay *tmp;
    for (auto it = _players_score.begin(); it < _players_score.end(); it++) {
        tmp = *it;
        tmp->update();
    }
    PlayerOverlay *p_tmp;
    for (auto it = _players_overlay.begin(); it < _players_overlay.end(); it++) {
        p_tmp = *it;
        p_tmp->update();
    }
}

void Overlay::pauseOverlay()
{
    int delta_s = time(nullptr) - _start;
    int time_elapsed = _time_limit - delta_s;
    if (time_elapsed != _time_left) {
        ScoreOverlay *tmp;
        for (auto it = _players_score.begin(); it < _players_score.end(); it++) {
            tmp = *it;
            tmp->pause(_time_left - time_elapsed);
        }
        _start += (_time_left - time_elapsed);
    }
}

const wchar_t *Overlay::getTime() {
    time_t now = time(nullptr);
    int delta_s = now - _start;
    _time_left = _time_limit - delta_s;
    int min = _time_left / 60;
    int sex = _time_left % 60;
    std::stringstream ss_sex;
    std::stringstream ss_min;
    ss_sex << std::setw(2) << std::setfill('0') << sex;
    ss_min << std::setw(2) << std::setfill('0') << min;
    std::string time_str = ss_min.str() + ":" + ss_sex.str();
    std::wstring *time_txt = new std::wstring(time_str.begin(), time_str.end());
    return time_txt->c_str();
}

bool Overlay::addScoreOverlay(std::string name, int playerNB) {
    if (_players_score.size() == 4)
        return false;
    _players_score.push_back(new ScoreOverlay(_env, _device, name, playerNB, _start));
    return true;
}

bool Overlay::addPlayerOverlay(IPlayer *player, std::string name)
{
    if (_players_overlay.size() == 4)
        return false;
    _players_overlay.push_back(new PlayerOverlay(_env, _smgr, player, name));
    return true;
}

ScoreOverlay::ScoreOverlay(IGUIEnvironment *env, IrrlichtDevice *device, std::string &name, int playerNB, time_t time, int def_score) :
    _name(name), _score(def_score), _start(time), _def_score(def_score) {
    std::stringstream ss;
    ss << name << " " << def_score;
    std::wstring *tmp = new std::wstring(ss.str().begin(), ss.str().end());
    switch(playerNB) {
        case 0:
            _overlay_name = env->addStaticText(tmp->c_str(), rect<s32>(0, 0, 600, 300));
            _overlay_name->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
            break;
        case 1:
            _overlay_name = env->addStaticText(tmp->c_str(), rect<s32>(device->getVideoModeList()->getDesktopResolution().Width-300,
                                                                0,
                                                                device->getVideoModeList()->getDesktopResolution().Width,
                                                                100));
            _overlay_name->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT);
            break;
        case 2:
            _overlay_name = env->addStaticText(tmp->c_str(), rect<s32>(0,
                                                                device->getVideoModeList()->getDesktopResolution().Height-100,
                                                                300,
                                                                device->getVideoModeList()->getDesktopResolution().Height));
            _overlay_name->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
            break;
        case 3:
            _overlay_name = env->addStaticText(tmp->c_str(), rect<s32>(device->getVideoModeList()->getDesktopResolution().Width-300,
                                                                device->getVideoModeList()->getDesktopResolution().Height-100,
                                                                device->getVideoModeList()->getDesktopResolution().Width,
                                                                device->getVideoModeList()->getDesktopResolution().Height
                                                                ));
            _overlay_name->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT);
            break;
        default:
            break;
    }
    _overlay_name->setOverrideColor(SColor(255,255,255,255));
}

void ScoreOverlay::update()
{
    time_t now = time(nullptr);
    if ((now - _start) >= 0) {
        _score = _def_score - (now - _start);
        std::stringstream ss;
        ss << _name << " " << _score;
        std::wstring *tmp = new std::wstring(ss.str().begin(), ss.str().end());
        _overlay_name->setText(tmp->c_str());
    } else
        _overlay_name->setText(L"");
}

void ScoreOverlay::pause(int delta_s) {
    _start += delta_s;
}

PlayerOverlay::PlayerOverlay(IGUIEnvironment *gui, ISceneManager *smgr, IPlayer *player, std::string &name) : _player(player), _name(name), _lives(player->getLives()) {
    std::wstringstream wss;
    for (int i = 0; i < 1; i++)
        wss << L"♥";
    std::wstring *tmp = new std::wstring(wss.str());
    _overlay_lives = smgr->addTextSceneNode(gui->getFont("media/font/lucida.xml"), tmp->c_str(), SColor(255,255,0,0));
    _overlay_lives->setPosition(_player->getPosition());
}

void PlayerOverlay::setLives(int lives) {
    _lives = lives;
}

void PlayerOverlay::update() {
    vector3df pos = _player->getPosition();
    pos.Y += 320;
    _overlay_lives->setPosition(pos);
}
