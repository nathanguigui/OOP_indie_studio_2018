/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** mymenu
*/

#ifndef MYMENU_HPP_
#define MYMENU_HPP_

#include "irrlicht/irrlicht.h"
#include <iostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "settings.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include "figure.hpp"

class MyMenu
{
public:
    MyMenu(IVideoDriver *, ISceneManager *, gui::IGUIEnvironment *, IrrlichtDevice *, bool);
    void addPlayer(int);
    void remPlayer();
    int getPlayerCount();
    void settings_toolbar(IGUIEnvironment *gui, bool val);
    ~MyMenu();
    IGUIWindow *settings_windows;
    IGUIScrollBar *map_size;
    IGUIScrollBar *scrollbar_music;
    IGUIScrollBar *scrollbar_sound;
    IGUICheckBox *splashscreen;
    IGUIEditBox *_editbox;
    IGUIListBox *_listbox;
    IGUIListBox *_skinlistbox;
    std::vector<Figure*> _figure;
    ITexture *_skin;
    IAnimatedMeshSceneNode *_skin_mesh;
    IGUIImage *_skin_image;
    ICameraSceneNode *_skin_camera;
    int _skin_id;
private:
};

struct SAppContext
{
    IrrlichtDevice *device;
    s32 counter = 0;
    s32 playerAdded = 0;
    s32 playerRemoved = 0;
    s32 startGame = 0;
    int set = 0;
    s32 id_close;
    s32 editing = 0;
    s32 enter_pressed = 0;
    bool splashscreen = true;
    BombermanSettings *settings;
    s32 skin_id = 1;
};

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_START_GAME,
    GUI_ID_SETTINGS,
    GUI_ID_ADD_PLAYER,
    GUI_ID_REM_PLAYER,
    GUI_ID_SOUND_SCROLL_BAR,
    GUI_ID_MUSIC_SCROLL_BAR,
    GUI_ID_EDITBOX,
    GUI_ID_BUTTON_SPLASHSCREEN,
    GUI_ID_CHANGE_SKIN,
    GUI_ID_OPEN_SKIN,
    GUI_ID_SIZE_MAP,
};

class MyMenuEventReceiver : public IEventReceiver
{
public:
    MyMenuEventReceiver(SAppContext &context) : Context(context) {}

    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE && !event.KeyInput.PressedDown)
        {
            Context.device->closeDevice();
        }
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment *env = Context.device->getGUIEnvironment();
            if (id == GUI_ID_BUTTON_SPLASHSCREEN) 
                Context.settings->set_splashscreen(!Context.settings->doSplashscreen());
            switch (event.GUIEvent.EventType)
            {
            case EGET_BUTTON_CLICKED:
                switch (id)
                {
                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
                    return true;
                case GUI_ID_ADD_PLAYER:
                    Context.playerAdded = 1;
                    return true;
                case GUI_ID_REM_PLAYER:
                    Context.playerRemoved = 1;
                    return true;
                case GUI_ID_START_GAME:
                    Context.startGame = 1;
                    return true;
                case GUI_ID_SETTINGS:
                    if (Context.set != 2)
                        Context.set = 1;
                    return true;
                case GUI_ID_CHANGE_SKIN:
                    Context.skin_id += (Context.skin_id != 4) ? 1 : (-Context.skin_id)+1;
                default:
                    return false;
                }
            default:
                break;
            case EGET_EDITBOX_MARKING_CHANGED:
                if (id == GUI_ID_EDITBOX) {
                    Context.editing = 1;
                    return true;
                }
            }
        }
        return false;
    }

private:
    SAppContext &Context;
};

#endif /* !MYMENU_HPP_ */