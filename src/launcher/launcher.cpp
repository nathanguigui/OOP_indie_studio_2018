/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** launcher
*/

#include "launcher.hpp"

BombermanLauncher::BombermanLauncher(bool value)
{
    _device = createDevice(EDT_OPENGL, dimension2d<u32> (1500, 750), 16, false);
    _driver = _device->getVideoDriver();
    _smgr = _device->getSceneManager();
    _gui = _device->getGUIEnvironment();
    _gui->getSkin()->setFont(_gui->getFont("media/font/myfont.xml"));
    s32 alpha = 255;
    for (u32 i = 0; i < EGDC_COUNT ; ++i) {
        SColor color = _gui->getSkin()->getColor ((EGUI_DEFAULT_COLOR)i);
        color.setAlpha (alpha);
        _gui->getSkin()->setColor ((EGUI_DEFAULT_COLOR)i, color);
    }
    main_menu = new MyMenu(_driver, _smgr, _gui, _device, value);
    if (!_ost.openFromFile("media/sound/ost.ogg"));
        std::cout << "File not found \n";
    _ost.play();
    _ost.setLoop(true);
}

void BombermanLauncher::setOstVolume(int volume)
{
    _ost.setVolume(volume);
}

MyMenu* BombermanLauncher::getMainMenu() {
    return main_menu;
}

void BombermanLauncher::addPlayer(BombermanSettings *settings, int i)
{
    if (main_menu->getPlayerCount() != 4)
        main_menu->addPlayer(i);
}

void BombermanLauncher::remPlayer(BombermanSettings *settings)
{
    main_menu->remPlayer();
}

bool BombermanLauncher::startGame(BombermanSettings *settings)
{
    if (main_menu->getPlayerCount() == 0)
        return false;
    for (int i = 0; i < main_menu->getPlayerCount(); i++) {
        std::wstring tmp = main_menu->_listbox->getListItem(i);
        std::wstring tmp_skin = main_menu->_skinlistbox->getListItem(i);
        std::string player(tmp.begin(), tmp.end());
        std::string skin(tmp_skin.begin(), tmp_skin.end());
        std::istringstream iss(skin);
        int skin_int;
        iss >> skin_int;
        std::cout << skin;
        settings->addPlayer(player, skin_int, i);
    }
    settings->startGame();
    return (true);
}

BombermanLauncher::~BombermanLauncher() {}

bool launcher_events(SAppContext &menu_context, BombermanLauncher *launcher, BombermanSettings *settings)
{
    if (menu_context.settings->isGameStarted())
        return false;
    if (menu_context.playerAdded) {
        std::wstring tmp = launcher->getMainMenu()->_editbox->getText();
        std::string content(tmp.begin(), tmp.end());
        if (content != "Enter up to 4 players" && content != "Enter player name here" && !content.empty())
            launcher->addPlayer(settings, menu_context.skin_id);
        menu_context.playerAdded = 0;
    } if (menu_context.set == 1) {
        launcher->getMainMenu()->settings_toolbar(launcher->_gui, settings->doSplashscreen());
        launcher->getMainMenu()->settings_windows->draw();
        menu_context.id_close = launcher->getMainMenu()->settings_windows->getCloseButton()->getID();
        menu_context.set = 2;
    } if (menu_context.playerRemoved) {
        launcher->remPlayer(settings);
        menu_context.playerRemoved = 0;
    } if (menu_context.startGame) {
        launcher->startGame(settings);
        menu_context.startGame = 0;
    } if (menu_context.editing) {
        menu_context.editing = 0;
        std::wstring tmp = launcher->getMainMenu()->_editbox->getText();
        std::string content(tmp.begin(), tmp.end());
        if (content == "Enter up to 4 players" || content == "Enter player name here")
            launcher->getMainMenu()->_editbox->setText(L"");
    } if (menu_context.skin_id != launcher->getMainMenu()->_skin_id) {
        launcher->getMainMenu()->_skin_id = menu_context.skin_id;
        switch (menu_context.skin_id) {
            case 1:
                launcher->getMainMenu()->_skin_mesh->setMaterialTexture(1, launcher->_driver->getTexture("media/colors/red.png"));
                break;
            case 2:
                launcher->getMainMenu()->_skin_mesh->setMaterialTexture(1, launcher->_driver->getTexture("media/colors/green.png"));
                break;
            case 3:
                launcher->getMainMenu()->_skin_mesh->setMaterialTexture(1, launcher->_driver->getTexture("media/colors/yellow.png"));
                break;
            case 4:
                launcher->getMainMenu()->_skin_mesh->setMaterialTexture(1, launcher->_driver->getTexture("media/colors/blue.png"));
                break;
        }
    } if (menu_context.set == 2) {
        settings->set_volume(launcher->getMainMenu()->scrollbar_sound->getPos(), launcher->getMainMenu()->scrollbar_music->getPos());
        launcher->setOstVolume(settings->get_music());
    }
    return true;
}

bool take_save(BombermanSettings *settings)
{
    FILE *file;
    std::string buffer = std::to_string(settings->get_sound()) + "\n" + std::to_string(settings->get_music()) + "\n";

    std::cout << "save created in /media/save.txt" << std::endl;
    file = fopen("media/save.txt", "w");
    if (file == NULL)
        return (0);
    fprintf(file, buffer.c_str());
    fclose(file);
    return (1);
}


BombermanSettings *start_launcher()
{
    s32 size;
    auto *settings = new BombermanSettings();
    auto *launcher = new BombermanLauncher(settings->get_splashscreen());
    ITexture *image;
    SAppContext menu_context;
    image = launcher->_driver->getTexture("./media/bombawallpaper.png");
    launcher->_device->setResizable(false);
    menu_context.device = launcher->_device;
    menu_context.settings = settings;
    MyMenuEventReceiver receive(menu_context);
    launcher->_device->setEventReceiver(&receive);
    while (launcher->_device->run()) {
        launcher->_driver->beginScene(true, true, SColor(255,100,101,140));
        launcher->_driver->setRenderTarget(launcher->getMainMenu()->_skin, true, true, video::SColor(0,0,0,255));
        launcher->_smgr->setActiveCamera(launcher->getMainMenu()->_skin_camera);
        launcher->_smgr->drawAll();
        launcher->_driver->setRenderTarget(0, true, true, 0);
        launcher->_driver->draw2DImage(image, rect<irr::s32>(0,0,1500,750), rect<s32>(0,0,1920,1080));
        launcher->_gui->drawAll();
        launcher->_driver->endScene();
        settings->set_volume(launcher->getMainMenu()->scrollbar_sound->getPos(),launcher->getMainMenu()->scrollbar_music->getPos());
        launcher->setOstVolume(settings->get_music());
        if (!launcher_events(menu_context, launcher, settings))
            break;
        size = launcher->getMainMenu()->map_size->getPos();
    }
    launcher->_ost.stop();
    settings->set_map_size(size);
    std::cout << settings->get_map_size() << std::endl;
    launcher->_device->drop();
    take_save(settings);
    return (settings);
}
