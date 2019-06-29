/*
** EPITECH PROJECT, 2019
** EventReceiver.hpp
** File description:
** Class for event receiver
*/

#pragma once

#include <iostream>
#include "irrlicht/irrlicht.h"


using namespace irr;
using namespace scene;
using namespace gui;

enum  GameGUI_ID {
    GUI_ID_PAUSE_RESUME = 124,
    GUI_ID_PAUSE_EXIT,
};

struct GameContext_s {
    bool game_paused = false;
    bool pause_clicked = false;
    bool resume_clicked = false;

};

namespace Gameplay {
	
	class EventReceiver : public IEventReceiver {

		public:

			EventReceiver(GameContext_s &context);
            ~EventReceiver();

			// Default method
			bool OnEvent(const SEvent& t_event);

			// For detecting keypressed
			bool IsKeyDown(EKEY_CODE keyCode) const;

			// Provide a function to be called on each event
			bool RegisterEvent();

		private:
			bool m_keyIsDown[KEY_KEY_CODES_COUNT];
			GameContext_s &Context;
	};
};
