/*
** EPITECH PROJECT, 2019
** IPlayer.hpp
** File description:
** Character interface
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include <string>
#include <vector>
#include "EventReceiver.hpp"
#include "bomb.hpp"

class GameMap;

// Namespace for all things relative to gameplay (player, powerups)
namespace Gameplay {

	//class EventReceiver;

	// An enum for the different return value of player action
	enum E_PLAYER_ACTION_ERROR {
	
		// Success
		EPERR_SUCCESS = 0,
	
		// Player could not move
		EPERR_MOVEMENT,
	
		// Player could not place bomb
		EPERR_BOMB,

        // Player could not pathfind
		EPERR_PATHFIND,
	};
	
	// An enum for different pickup items
	enum E_PLAYER_PICKUP {
	
		// Bomb up
		EPI_BOMB = 0,
	
		// Fire up
		EPI_FIRE,

        // Speed up
        EPI_SPEED,
	};

	/*
	Player interface. move, action and pickup function
	all return 0 if successful
	*/
	class IPlayer {
	    public:
	    	virtual ~IPlayer() {};

	    	virtual int pollEvents(irr::IrrlichtDevice* t_device, EventReceiver receiver, GameMap* t_map, std::vector<IPlayer*> t_players) = 0;
	    	virtual int pickup(E_PLAYER_PICKUP t_pickup) = 0;

	    	virtual size_t getBomb() const = 0;
	    	virtual size_t getFire() const = 0;
	    	virtual size_t getSpeed() const = 0;
			virtual size_t getLives() const = 0;
			virtual std::vector<Bomb *> getVector() const = 0;
	    	virtual irr::core::vector3df getPosition() const = 0;
	    	virtual irr::scene::IAnimatedMeshSceneNode* getSceneNode() const = 0;
			virtual std::wstring getName() const = 0;

	    	virtual void setBomb(size_t t_bomb) = 0;
	    	virtual void setFire(size_t t_fire) = 0;
	    	virtual void setSpeed(size_t t_speed) = 0;
			virtual void setLives(size_t t_lives) = 0;
	    	virtual void setPosition(irr::core::vector3df t_pos) = 0;
			virtual void setName(std::wstring t_name) = 0;
			virtual void setNodePosition(irr::core::vector3df t_pos) = 0;
			virtual bool isAlive() const = 0;

	    protected:
	    	std::wstring m_name;
	    	size_t m_bomb { 1 };
	    	size_t m_avail { m_bomb };
	    	size_t m_fire { 1 };
	    	size_t m_speed { 1 };
	    	size_t m_lives { 3 };
			size_t m_onScreen { 0 };
	    	irr::EKEY_CODE m_keyBindings[5] { 
	    		irr::KEY_KEY_S,
	    		irr::KEY_KEY_Z,
	    		irr::KEY_KEY_D,
	    		irr::KEY_KEY_Q,
	    		irr::KEY_SPACE 
	    	};
	    	irr::f32 m_MAX_SPEED = 10.0f;
	    	irr::f32 m_ACCELERATION = 30.f;
	    	irr::scene::IAnimatedMesh* m_mesh;
	    	irr::scene::IAnimatedMeshSceneNode* m_node;
			irr::scene::ITextSceneNode* m_nameTextNode;
	    	irr::u32 m_then;
			std::vector<Bomb *> _bombs;
	};

}; // end namespace Gameplay
