/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** game
*/

#include "game.hpp"

BombermanGame::BombermanGame(EventReceiver receiver, BombermanSettings *settings) : _settings(settings), _receiver(receiver) {
    _device = createDevice(EDT_OPENGL, dimension2d<u32> (1920, 1080), 16, true, false, false, &_receiver);
    _driver = _device->getVideoDriver();
    _smgr = _device->getSceneManager();
    _gui = _device->getGUIEnvironment();
    _driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
    _smgr->addSkyDomeSceneNode(_driver->getTexture("media/black.png"),16,8,0.95f,2.0f);
    _driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
    rip  = 0;
    if (_settings->doSplashscreen())
        splashScreen();
    _map = new GameMap(_driver, _smgr, _settings->get_map_size());
    _overlay = new Overlay(_gui, _smgr, _device, 600, 250);
    for (size_t index = 0; index < _settings->getPlayerCount(); index++) {
        // Changing for better code: ctor, playerSetPos etc
        BomberPlayer *player = new BomberPlayer(
            _device,
            _settings->getPlayerList()[index]->getName(),
            _settings->getPlayerList()[index]->getTexture(_driver),
            _settings->getPlayerList()[index]->getKeyBindings());
        player->setNodePosition(_map->getSpawnPoint(index));
        _map->setCollision(player);
        _overlay->addScoreOverlay(_settings->getPlayerList()[index]->getName(), index);
        _overlay->addPlayerOverlay(player, _settings->getPlayerList()[index]->getName());
        _players.push_back(player);
    }
    _menu = new PauseMenu(_gui, _device);
    _paused = false;
}

BombermanGame::~BombermanGame()
{
    _device->drop();
}

void BombermanGame::pollAllEvents() {
    for (int i = 0; i == 0; i++)//<_players.size(); i++)
        rip = _players[i]->pollEvents(_device, _receiver, _map, this->getPlayers());
}

void BombermanGame::play()
{
    _driver->beginScene(true, true, SColor(255,0,0,0));
    if (rip == this->_players.size() - 1) {
            IGUIStaticText *gg = _gui->addStaticText(L"GG YOU WIN", rect<s32>(860, 500, 1260, 700), false, true,0);
            IGUIStaticText *gg2 = _gui->addStaticText(L"PRESS ECHAP TO LEAVE", rect<s32>(760, 710, 1260, 1000), false, true,0);
            gg->setOverrideColor(SColor(255,255,255,255));
            gg2->setOverrideColor(SColor(255,255,255,255));
    }
    _overlay->updateOverlay();
    _smgr->drawAll();
    _gui->drawAll();
    pollAllEvents();
    _driver->endScene();
}

void BombermanGame::splashScreen()
{
    int i = 0;
    ITexture *background;
    _splash_sound.openFromFile("media/sound/ps1.ogg");
    _splash_sound.play();
    _splash_sound.setVolume(_settings->get_music());
    while (_device->run() && i < 510) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << i;
        std::string tmp = "media/splash/splash" + ss.str() + ".png";
        background = _driver->getTexture(tmp.c_str());
        _driver->beginScene(true, true, SColor(255,100,101,140));
        _driver->draw2DImage(background,
                rect<irr::s32>(0,0,_device->getVideoModeList()->getDesktopResolution().Width,_device->getVideoModeList()->getDesktopResolution().Height),
                rect<s32>(0,0,1280,720),
                0,0,true);
        _driver->endScene();
        _driver->removeTexture(background);
        i++;
    }
    _splash_sound.stop();
}

bool BombermanGame::run() {
    return _device->run();
}

void BombermanGame::pause() {
    _driver->beginScene(true, true, SColor(255,0,0,0));
    _overlay->pauseOverlay();
    _menu->draw();
    _driver->endScene();
}

void BombermanGame::unpause()
{
    _menu->remove();
}

void game_events(GameContext_s &app_context, BombermanGame *game) {
   if (app_context.game_paused != game->_paused) {
       if (game->_paused) {
           game->unpause();
           game->_paused = false;
       } else
           game->_paused = true;
   }
    /*if (app_context.pause_clicked && !game->_paused)
        game->_paused = true;
    else if (app_context.resume_clicked && game->_paused) {
        game->unpause();
        game->_paused = false;
    }*/
}

void start_game(BombermanSettings *settings)
{
    if (!settings->isGameStarted())
        return;
    GameContext_s app_context;
    EventReceiver receiver(app_context);
    BombermanGame *game = new BombermanGame(receiver, settings);
    while (game->run()) {
        game_events(app_context, game);
        if (game->_paused)
            game->pause();
        else
            game->play();
    }
    game->~BombermanGame();
}
