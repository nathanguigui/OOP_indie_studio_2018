/*
** EPITECH PROJECT, 2019
** BomberPlayer.cpp
** File description:
** Player character class source file
*/

#include "BomberPlayer.hpp"
#include "map.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace io;

using namespace Gameplay;
int death = 0;

BomberPlayer::BomberPlayer(irr::IrrlichtDevice* t_device)
{
	std::cerr << "Creating player character" << std::endl;
	m_mesh = t_device->getSceneManager()->getMesh("./media/sydney.md2");
	if (!m_mesh) {
		std::cerr << "error: could not load player model\n";
		t_device->drop();
	}
	
	m_node = t_device->getSceneManager()->addAnimatedMeshSceneNode(m_mesh);
	if (m_node) {
		m_node->setPosition(core::vector3df(0, 0, 0));
		m_node->setMaterialFlag(video::EMF_LIGHTING, false);
		m_node->setMD2Animation(scene::EMAT_STAND);
		m_node->setMaterialType(video::EMT_REFLECTION_2_LAYER);
		m_node->setMaterialTexture(
			0, t_device->getVideoDriver()->getTexture("./media/sydney.bmp"));
		m_node->setScale(vector3df(10, 10, 10));
	}
	m_then = t_device->getTimer()->getTime();
	irr::core::vector3df nodePos = m_node->getPosition();

	IGUIFont* t_font = t_device->getGUIEnvironment()->getFont("media/font/myfont.xml");
	m_nameTextNode = t_device->getSceneManager()->addTextSceneNode(t_font, L"Unavailable", irr::video::SColor (43, 139, 243, 1), m_node, 
	vector3df (nodePos.X, nodePos.Y + 400, nodePos.Z), -1);
}

BomberPlayer::BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name)
	: BomberPlayer(t_device)
{
	m_name = std::wstring (t_name.begin(), t_name.end());
	m_nameTextNode->setText(m_name.c_str());
}

BomberPlayer::BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture)
	: BomberPlayer(t_device, t_name)
{
	m_node->setMaterialTexture(1, t_texture);
}

BomberPlayer::BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture, EKEY_CODE t_keyBindings[5])
	: BomberPlayer(t_device, t_name, t_texture)
{
	this->setKeyBindings(t_keyBindings);
	std::cerr << "got there" << std::endl;
}

/* BomberPlayer::BomberPlayer(irr::IrrlichtDevice* t_device, std::string t_name, irr::video::ITexture* t_texture, const EKEY_CODE t_keyBindings[5])
{
	this->setKeyBindings(t_keyBindings);
}*/

int BomberPlayer::is_hit(Bomb *b, std::vector<IPlayer *> _players)
{
	std::cout << b->getPosition().Z << " " << b->getPosition().X << "\n";	
    for (int i = 0; i < _players.size();i++) {
		if (_players[i]->getPosition().Z == b->getPosition().Z &&_players[i]->getPosition().X == b->getPosition().X) {
			_players[i]->setPosition(vector3df(10000, 10000, 10000));
			death++;
		}
		if (_players[i]->getPosition().Z - 255 == b->getPosition().Z && _players[i]->getPosition().X == b->getPosition().X) {
			_players[i]->setPosition(vector3df(10000, 10000, 10000));
			death++;
		}
		if (_players[i]->getPosition().Z + 255 == b->getPosition().Z && _players[i]->getPosition().X == b->getPosition().X) {
			_players[i]->setPosition(vector3df(10000, 10000, 10000));
			death++;
		}
		if (_players[i]->getPosition().X - 255 == b->getPosition().X && _players[i]->getPosition().Z == b->getPosition().Z) {
			_players[i]->setPosition(vector3df(10000, 10000, 10000));
			death++;
		}
		if (_players[i]->getPosition().X + 255 == b->getPosition().X && _players[i]->getPosition().Z == b->getPosition().Z) {
			_players[i]->setPosition(vector3df(10000, 10000, 10000));
			death++;
		}
		std::cout << i <<" " <<_players[i]->getPosition().Z << " " << _players[i]->getPosition().X<< std::endl;
    }
	return (death);
} 

void BomberPlayer::updateBombs(IrrlichtDevice *device, GameMap *map, std::vector<IPlayer*> t_players)
{
    for (int i = 0; i < _bombs.size(); ++i)
    {
        if ( _bombs[i]->getDeltaTime() >= 2000) {
			_bombs[i]->explodeIt();
			map->explodeWall(_bombs[i]->getPosition(), _bombs[i]->getRadius());
			if (_bombs[i]->hasEnd()) {
				is_hit(_bombs[i], t_players);
				delete _bombs[i];
				_bombs.erase(_bombs.begin() + i);
				m_onScreen -= 1;
				m_avail += 1;
			}
		}
	}
}

int BomberPlayer::pollEvents(irr::IrrlichtDevice* t_device, EventReceiver receiver, GameMap* t_map, std::vector<IPlayer*> t_players)
{
	irr::core::vector3df nodePos = m_node->getPosition();
    (void) t_players;
	bool k = false;

	if (m_lives <= 0)
		return 1;

	m_nameTextNode->setPosition(irr::core::vector3df (nodePos.X, nodePos.Y + 400, nodePos.Z));
	processMoves(t_device, receiver);
	processBombs(t_device, receiver, t_map);
	if (m_onScreen > 0) {
		updateBombs(t_device, t_map, t_players);
	}
	return death;
}

int BomberPlayer::pickup(E_PLAYER_PICKUP t_pickup)
{
    switch (t_pickup) {
        case EPI_BOMB:
            this->setBomb(m_bomb + 1);
            break;
        case EPI_FIRE:
            this->setFire(m_fire + 1);
            break;
        case EPI_SPEED:
            this->setSpeed(m_speed + 1);
            break;
    }
    return 0;
}

size_t BomberPlayer::getBomb() const
{
        return m_bomb;
}

size_t BomberPlayer::getFire() const
{
        return m_fire;
}

size_t BomberPlayer::getSpeed() const
{
        return m_speed;
}

size_t BomberPlayer::getLives() const
{
	return m_lives;
}

irr::core::vector3df BomberPlayer::getPosition() const
{
    return m_node->getPosition();
}

irr::scene::IAnimatedMeshSceneNode* BomberPlayer::getSceneNode() const
{
	return m_node;
}

std::wstring BomberPlayer::getName() const
{
	return m_name;
}

std::vector<Bomb *> BomberPlayer::getVector() const
{
	return _bombs;
}

void BomberPlayer::setBomb(size_t t_bomb)
{
	m_bomb = t_bomb;
}

void BomberPlayer::setFire(size_t t_fire)
{
	m_fire = t_fire;
}

void BomberPlayer::setSpeed(size_t t_speed)
{
	m_MAX_SPEED /= m_speed;
    m_ACCELERATION /= m_speed;
    m_speed = t_speed;
    m_MAX_SPEED *= m_speed;
    m_ACCELERATION *= m_speed;
}

void BomberPlayer::setPosition(irr::core::vector3df t_pos)
{
	m_node->setPosition(t_pos);
}

void BomberPlayer::setLives(size_t t_lives)
{
	m_lives = t_lives;

	if (m_lives = 0) {
		std::cerr << "Player died" << std::endl;
	}
}

void BomberPlayer::setName(std::wstring t_name)
{
	m_name = t_name;
}

void BomberPlayer::setNodePosition(irr::core::vector3df t_pos)
{
	m_node->setPosition(t_pos);
}

bool BomberPlayer::isAlive() const
{
	if (m_lives > 0)
		return true;
	return false;
}

void BomberPlayer::setKeyBindings(EKEY_CODE t_keyBindings[5])
{
	for (size_t index = 0; index != 5; index++)
		m_keyBindings[index] = t_keyBindings[index];
}

void BomberPlayer::setKeyBindings(const EKEY_CODE t_keyBindings[5])
{
	for (size_t index = 0; index != 5; index++)
		m_keyBindings[index] = t_keyBindings[index];
}

void BomberPlayer::processStraightMove(vector3df& playerVelocity, EventReceiver receiver, f32 frameDeltaTime)
{
	if (receiver.IsKeyDown(m_keyBindings[0])) {
		playerVelocity.X += m_ACCELERATION * frameDeltaTime;
		playerVelocity.X = playerVelocity.X > m_MAX_SPEED ? m_MAX_SPEED : playerVelocity.X;
	} else if (receiver.IsKeyDown(m_keyBindings[1])) {
		playerVelocity.X -= m_ACCELERATION * frameDeltaTime;
		playerVelocity.X = playerVelocity.X < -m_MAX_SPEED ? -m_MAX_SPEED : playerVelocity.X;
	} else {
		if (playerVelocity.X < 0) {
			playerVelocity.X += m_ACCELERATION * frameDeltaTime;
			playerVelocity.X = playerVelocity.X >= 0 ? 0.0f : playerVelocity.X;
		} else {
			playerVelocity.X -= m_ACCELERATION * frameDeltaTime;
			playerVelocity.X = playerVelocity.X <= 0 ? 0.0f : playerVelocity.X;
		}
	}
}

void BomberPlayer::processSideMove(vector3df& playerVelocity, EventReceiver receiver, f32 frameDeltaTime)
{
	if (receiver.IsKeyDown(m_keyBindings[2])) {
		playerVelocity.Z += m_ACCELERATION * frameDeltaTime;
		playerVelocity.Z = playerVelocity.Z > m_MAX_SPEED ? m_MAX_SPEED : playerVelocity.Z;
	} else if (receiver.IsKeyDown(m_keyBindings[3])) {
		playerVelocity.Z -= m_ACCELERATION * frameDeltaTime;
		playerVelocity.Z = playerVelocity.Z < -m_MAX_SPEED ? -m_MAX_SPEED : playerVelocity.Z;
	} else {
		if (playerVelocity.Z < 0) {
			playerVelocity.Z += m_ACCELERATION * frameDeltaTime;
			playerVelocity.Z = playerVelocity.Z >= 0 ? 0.0f : playerVelocity.Z;
		} else {
			playerVelocity.Z -= m_ACCELERATION * frameDeltaTime;
			playerVelocity.Z = playerVelocity.Z <= 0 ? 0.0f : playerVelocity.Z;
		}
	}
}

E_PLAYER_ACTION_ERROR BomberPlayer::processMoves(irr::IrrlichtDevice* t_device, EventReceiver receiver)
{
	const irr::u32 now = t_device->getTimer()->getTime();
	const irr::f32 frameDeltaTime = (f32) (now - m_then) / 1000.f;
	static irr::core::vector3df playerVelocity (0, 0, 0);

	m_then = now;

	processStraightMove(playerVelocity, receiver, frameDeltaTime);
	processSideMove(playerVelocity, receiver, frameDeltaTime);

	m_node->setPosition(m_node->getPosition() + playerVelocity);
	return EPERR_SUCCESS;
}

E_PLAYER_ACTION_ERROR BomberPlayer::processBombs(irr::IrrlichtDevice* t_device,
						EventReceiver t_receiver, GameMap* t_map)
{
	if (t_receiver.IsKeyDown(m_keyBindings[4]) && m_avail > 0) {
		m_onScreen += 1;
		m_avail -= 1;
		Bomb *b = new Bomb(m_node->getPosition(), t_device, m_fire);
		_bombs.push_back(b);
		std::cerr << "Bomb dropped" << std::endl;
	}
	return EPERR_SUCCESS;
}