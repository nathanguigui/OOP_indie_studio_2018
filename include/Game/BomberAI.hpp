/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** BomberAI
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "game.hpp"
#include <IPlayer.hpp>
#include <bomb.hpp>
#include <iostream>
#include <string>
#include <algorithm>

namespace Gameplay {
    
    class BomberAI : public IPlayer {
    	public:
    		BomberAI(irr::IrrlichtDevice *t_device);
    		~BomberAI();

        public:

			// Run this each time you want to test for user-triggered events
			int pollEvents(irr::IrrlichtDevice* t_device, EventReceiver receiver, GameMap* t_map, std::vector<IPlayer*> t_players);			

			// Indicate an item was picked-up
			int pickup(E_PLAYER_PICKUP t_pickup);

            // specific setters
			void setBomb(size_t t_bomb) { m_bomb = t_bomb; };
			void setFire(size_t t_fire) { m_fire = t_fire; };
			void setSpeed(size_t t_speed);
            void setLives(size_t t_lives) { m_lives = t_lives; };
			void setPosition(irr::core::vector3df t_pos);
			void setName(std::wstring t_name) { m_name = t_name; };
            void setNodePosition(irr::core::vector3df t_pos) { m_node->setPosition(t_pos); };

            // specific getters
            IPlayer *getClosestPlayer(std::vector<IPlayer*> players);
            size_t getDist(irr::core::vector3df aPos, irr::core::vector3df bPos);
			size_t getBomb() const { return m_bomb; };
			size_t getFire() const { return m_fire; };
            size_t getSpeed() const { return m_speed; };
            size_t getLives() const { return m_lives; };
            std::vector<Bomb *> getVector() const { return _bombs; };
            bool isAlive() const { return m_lives > 0; }
            irr::core::vector3df getPosition() const { return m_node->getPosition(); };
			irr::scene::IAnimatedMeshSceneNode* getSceneNode() const { return m_node; };
			std::wstring getName() const { return m_name; };

		private: // methods
            E_PLAYER_ACTION_ERROR processMoves(irr::IrrlichtDevice* t_device, GameMap *t_map);
            void movePlayer(vector3df& playerVelocity, vector2df dir, f32 frameDeltaTime);            
            E_PLAYER_ACTION_ERROR processBombs(irr::IrrlichtDevice* t_device, GameMap* t_map);

            bool posIsOnMap(vector2df pos, GameMap *t_map);
            bool posIsWalkable(vector2df pos, GameMap *t_map);
            bool isInBombRange(GameMap *t_map, vector2df testPos, vector2df *supPos);
            vector2df *newHidingSpot(GameMap *t_map, vector2df *supPos = nullptr);
        
        private: // path finding;
            void setUpNodes(GameMap *t_map);
            bool Solve_AStar(GameMap *t_map);	
            bool findPath(GameMap *t_map, vector2df start, vector2df end);

            struct sNode {
		        bool bObstacle = false;			// Is the node an obstruction?
		        bool bDestroyable = false;		// Is the node a destructible block?
		        bool bVisited = false;			// Have we searched this node before?
		        float fGlobalGoal;				// Distance to goal so far
		        float fLocalGoal;				// Distance to goal if we took the alternative route
		        int x;							// Nodes position in 2D space
		        int y;
		        std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		        sNode* parent;					// Node connecting to this node that offers shortest parent
	        };

            bool m_isSetUp = false;
            sNode *nodes = nullptr;
            sNode *nodeStart = nullptr;
	        sNode *nodeEnd = nullptr;

            vector2df goal;
            std::vector<vector2df> bombsPos;
    };
}