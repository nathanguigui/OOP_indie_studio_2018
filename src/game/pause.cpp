/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** pause.cpp
*/

#include "pause.hpp"

PauseMenu::PauseMenu(IGUIEnvironment *gui, IrrlichtDevice *device) {
    int width = device->getVideoModeList()->getDesktopResolution().Width;
    int height = device->getVideoModeList()->getDesktopResolution().Height;
    _resume = gui->addButton(rect<s32>((width/2)-200, height/10*3.5, (width/2)+200, height/10*3.5+100), 0, GUI_ID_PAUSE_RESUME, L"Resume");
    _exit = gui->addButton(rect<s32>((width/2)-200, height/10*5.5, (width/2)+200, height/10*5.5+100), 0, GUI_ID_PAUSE_EXIT, L"Exit");
    _resume->draw();
    _exit->draw();
    _resume->setVisible(false);
    _exit->setVisible(false);
}

void PauseMenu::draw()
{
    _resume->setVisible(true);
    _resume->draw();
    _exit->draw();
}

void PauseMenu::remove()
{
    _resume->setVisible(false);
    _exit->setVisible(false);
}