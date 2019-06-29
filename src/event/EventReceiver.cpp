/*
** EPITECH PROJECT, 2019
** EventReceiver.hpp
** File description:
** Methods for event receiver class
*/

#include "EventReceiver.hpp"

using namespace Gameplay;

using namespace irr;
using namespace core;
using namespace scene;

EventReceiver::EventReceiver(GameContext_s &context) : Context(context)
{
	for (irr::u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
		m_keyIsDown[i] = false;
}

EventReceiver::~EventReceiver() {}

/* Add a function that registers an event function. and calls it here. */
bool EventReceiver::OnEvent(const SEvent& t_event)
{
	if (t_event.EventType == EET_KEY_INPUT_EVENT) {
        if (t_event.KeyInput.Key == KEY_ESCAPE && !t_event.KeyInput.PressedDown) {
            std::cerr << "Quitting game..." << std::endl;
            exit(0);
        } if (t_event.KeyInput.Key == KEY_KEY_P && !t_event.KeyInput.PressedDown)
            Context.game_paused = true;
		m_keyIsDown[t_event.KeyInput.Key] = t_event.KeyInput.PressedDown;
	} if (t_event.EventType == EET_GUI_EVENT) {
	    if (t_event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
            s32 id = t_event.GUIEvent.Caller->getID();
            switch (id) {
                case GUI_ID_PAUSE_RESUME:
                    Context.game_paused = false;
                    break;
                default:
                    break;
            }
        }
	}
	return false;
}

bool EventReceiver::IsKeyDown(EKEY_CODE t_keyCode) const
{
	return m_keyIsDown[t_keyCode];
}

void setKeybindings(EKEY_CODE t_keyCode[4])
{

}
