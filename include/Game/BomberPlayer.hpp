/*
** EPITECH PROJECT, 2019
** BomberPlayer.hpp
** File description:
** Player character class
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "game.hpp"
#include "IPlayer.hpp"
#include "EventReceiver.hpp"
#include <bomb.hpp>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace io;

namespace Gameplay {

	// Player controlled character
	class BomberPlayer : public IPlayer {
		public:

			BomberPlayer(irr::IrrlichtDevice* t_device);
			BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name);
			BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture);
			BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture, EKEY_CODE keyBindings[5]);
			//BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture, const EKEY_CODE keyBindings[5]);

			// Run this each time you want to test for user-triggered events
			int pollEvents(irr::IrrlichtDevice* t_device, EventReceiver receiver, GameMap* t_map, std::vector<IPlayer*> t_players);
			int is_hit(Bomb *, std::vector<IPlayer *> players);
			// Indicate an item was picked-up
			int pickup(E_PLAYER_PICKUP t_pickup);

			size_t getBomb() const;
			size_t getFire() const;
            size_t getSpeed() const;
			size_t getLives() const;
			std::vector<Bomb *> getVector() const;

			// Returns the m_node position
			irr::core::vector3df getPosition() const;

			irr::scene::IAnimatedMeshSceneNode* getSceneNode() const;
			std::wstring getName() const;

			void setBomb(size_t t_bomb);
			void setFire(size_t t_fire);
			void setSpeed(size_t t_speed);
			void setLives(size_t t_lives);
			void setPosition(irr::core::vector3df t_pos);
			void setName(std::wstring t_name);
			void setNodePosition(irr::core::vector3df t_pos);

            bool isAlive() const;

			/*
			index to action:
			[0]: move forward
			[1]: move backwards
			[2]: move left
			[3]: move right
			[4]: place bomb
			*/
			void setKeyBindings(EKEY_CODE t_keyBindings[5]);
			void setKeyBindings(const EKEY_CODE t_keyBindings[5]);
			void updateBombs(IrrlichtDevice *t_device, GameMap* t_map, std::vector<IPlayer*> t_players);
		private:

			E_PLAYER_ACTION_ERROR processBombs(irr::IrrlichtDevice* t_device, EventReceiver t_receiver, GameMap* t_map);
			E_PLAYER_ACTION_ERROR processMoves(irr::IrrlichtDevice* t_device, EventReceiver receiver);
			void processStraightMove(vector3df& playerVelocity, EventReceiver receiver, f32 fDT);
			void processSideMove(vector3df& playerVelocity, EventReceiver receiver, f32 fDT);
	};

}; // end namespace gameplay
