/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** menu
*/

#include "menu.hpp"

bool get_save(int &sound, int &music)
{
    std::cout << "save loaded in /media/save.txt" << std::endl;
    FILE* fp = fopen("media/save.txt", "r");
    if (fp == NULL)
        return (0);

    char* line = NULL;
    size_t len = 0;
    int i = 0;
    while ((getline(&line, &len, fp)) != -1) {
        printf("--%s", line);
        if (i == 0) {
            sound = atoi(line);
            printf("%d\n", sound);
        }
        if (i == 1) {
            music = atoi(line);
            printf("%d\n", music);
        }
        i++;
    }
    fclose(fp);
    if (line)
        free(line);
    return (1);
}

MyMenu::MyMenu(IVideoDriver *driver, ISceneManager *smgr, gui::IGUIEnvironment *gui, IrrlichtDevice *device, bool splash)
{
    int sound = 100;
    int music = 100;
    printf("**%d\n**%d\n", sound, music);


    get_save(sound, music);

    printf("**%d\n**%d\n", sound, music);

    _editbox = gui->addEditBox(L"Enter player name here", rect<s32>(50, 50, 400, 100), true, 0, GUI_ID_EDITBOX);
    _listbox = gui->addListBox(rect<s32>(50, 100, 350, 300));
    _skinlistbox = gui->addListBox(rect<s32>(350, 100, 400, 300));
    gui->addButton(rect<s32>(50, 600, 250, 700), 0, GUI_ID_QUIT_BUTTON,
                   L"Quit", L"Exits Program");
    gui->addButton(rect<s32>(450, 50, 650, 150), 0, GUI_ID_ADD_PLAYER,
                   L"Add player");
    gui->addButton(rect<s32>(450, 200, 650, 300), 0, GUI_ID_REM_PLAYER,
                   L"Remove player");
    gui->addButton(rect<s32>(700, 50, 900, 150), 0, GUI_ID_CHANGE_SKIN,
                   L"Change Skin");
    gui->addButton(rect<s32>(1250,600,1450, 700), 0, GUI_ID_START_GAME,
                   L"Launch Game", L"");

        gui->addStaticText(L"Music:", rect<s32>(500, 400, 650, 440), false, true,0);
	scrollbar_music = gui->addScrollBar(true,
			rect<s32>(500, 450, 1100, 500), 0, GUI_ID_MUSIC_SCROLL_BAR);
    gui->addStaticText(L"Sound:", rect<s32>(500, 500, 650, 540), false, true,0);
	scrollbar_sound = gui->addScrollBar(true,
			rect<s32>(500, 550, 1100, 600), 0, GUI_ID_SOUND_SCROLL_BAR);
    gui->addStaticText(L"Splashscreen:", rect<s32>(500, 700, 700, 770), false, true, 0);
    splashscreen = gui->addCheckBox(splash, rect<s32>(700, 700, 715, 715), 0, GUI_ID_BUTTON_SPLASHSCREEN);
	scrollbar_music->setMax(100);
	scrollbar_music->setPos(music);
    scrollbar_sound->setMax(100);
    scrollbar_sound->setPos(sound);
    gui->addStaticText(L"Size Map", rect<s32>(40, 420, 350, 450), 0, 0);
    map_size = gui->addScrollBar(true, rect<s32>(50, 450, 350, 500),0, GUI_ID_SIZE_MAP);
    map_size->setMax(1);
    map_size->setPos(0);
    _skin_mesh = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/sydney.md2"));
    _skin_mesh->setMaterialFlag(EMF_LIGHTING, false);
    _skin_mesh->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
    _skin_mesh->setMaterialTexture(1, driver->getTexture("media/colors/red.png"));
    _skin_mesh->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    _skin_mesh->setPosition(core::vector3df(-10,0,-100));
    _skin_mesh->setScale(vector3df(2.1, 2.1,2.6));
    _skin_mesh->setMD2Animation(scene::EMAT_STAND);
    smgr->addLightSceneNode(0, core::vector3df(-15,5,-105), video::SColorf(1.0f, 1.0f, 1.0f));
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    smgr->setAmbientLight(video::SColor(0,60,60,60));
    _skin = driver->addRenderTargetTexture(dimension2d<u32>(500, 500), "RTT1");
    _skin_image = gui->addImage(_skin, position2d<s32>(950, 50));
    _skin_camera = smgr->addCameraSceneNode(0, core::vector3df(70,20,-80), core::vector3df(-10,10,-100));
    _skin_id = 1;
}

void MyMenu::addPlayer(int i)
{
    _listbox->addItem(_editbox->getText());
    _skinlistbox->addItem(std::to_wstring(i).c_str());
    if (_listbox->getItemCount() == 4)
        _editbox->setText(L"It's time to go !");
    else
        _editbox->setText(L"Enter up to 4 players");
}

int MyMenu::getPlayerCount()
{
    int count = _listbox->getItemCount();
    return count;
}

void MyMenu::remPlayer()
{
    _skinlistbox->removeItem((_listbox->getSelected()));
    _listbox->removeItem(_listbox->getSelected());
    if (_listbox->getItemCount() != 4)
        _editbox->setText(L"Enter up to 4 players");
}

void MyMenu::settings_toolbar(IGUIEnvironment *gui, bool splash)
{

}

MyMenu::~MyMenu() {

}