/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** BomberAI
*/

#include <BomberAI.hpp>
#include "map.hpp"
#include <list>

using namespace Gameplay;

void BomberAI::setUpNodes(GameMap *t_map)
{
    int nMapWidth = t_map->getSize().X;
    int nMapHeight = t_map->getSize().Y;

    m_isSetUp = true;
	nodes = new sNode[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++) {
			nodes[y * nMapWidth + x].x = x;
			nodes[y * nMapWidth + x].y = y;
            switch (t_map->getMap()[y][x]) {
                case '1':
			        nodes[y * nMapWidth + x].bObstacle = true;
			        nodes[y * nMapWidth + x].bDestroyable = false;
                    break;
                case '2':
                    nodes[y * nMapWidth + x].bObstacle = false;
			        nodes[y * nMapWidth + x].bDestroyable = true;
                    break;
                default:
                    nodes[y * nMapWidth + x].bObstacle = false;
			        nodes[y * nMapWidth + x].bDestroyable = false;
                    break;
            }
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
		}

	// Create connections - in this case nodes are on a regular grid
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++) {
			if (y > 0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			if (y < nMapHeight - 1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			if (x > 0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			if (x < nMapWidth - 1)
					nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);
        }

	// Manually positio the start and end markers so they are not nullptr
	nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
	nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth-2];
}

bool BomberAI::Solve_AStar(GameMap *t_map)
{
    int nMapWidth = t_map->getSize().X;
    int nMapHeight = t_map->getSize().Y;

	// Reset Navigation Graph - default all node states
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++) {
			nodes[y*nMapWidth + x].bVisited = false;
			nodes[y*nMapWidth + x].fGlobalGoal = INFINITY;
			nodes[y*nMapWidth + x].fLocalGoal = INFINITY;
			nodes[y*nMapWidth + x].parent = nullptr;	// No parents
		}

	auto distance = [](sNode* a, sNode* b) { // For convenience
		return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b) { // So we can experiment with heuristic
		return distance(a, b);
	};

	// Setup starting conditions
	sNode *nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	// Add start node to not tested list - this will ensure it gets tested.
	// As the algorithm progresses, newly discovered nodes get added to this
	// list, and will themselves be tested later
	std::list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	// if the not tested list contains nodes, there may be better paths
	// which have not yet been explored. However, we will also stop 
	// searching when we reach the target - there may well be better
	// paths but this one will do - it wont be the longest.
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd) { // Find absolutely shortest path // && nodeCurrent != nodeEnd)
		// Sort Untested nodes by global goal, so lowest is first
	    listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		// Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...
		while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		// ...or abort because there are no valid nodes left to test
		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true; // We only explore a node once
			
					
		// Check each of this node's neighbours...
		for (auto nodeNeighbour : nodeCurrent->vecNeighbours) {
			// ... and only if the neighbour is not visited and is 
			// not an obstacle, add it to NotTested List
			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
				listNotTestedNodes.push_back(nodeNeighbour);

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			// If choosing to path through this node is a lower distance than what 
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set its distance scores as necessary
			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal) {
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}	
	}
	return true;
}

bool BomberAI::findPath(GameMap *t_map, vector2df start, vector2df end)
{
    int nMapWidth = t_map->getSize().X;
    int nMapHeight = t_map->getSize().Y;

    if (!posIsWalkable(start, t_map) || !posIsWalkable(end, t_map))
        return false;

    nodeStart = &nodes[(int)(start.Y * nMapHeight + start.X)];
    nodeEnd = &nodes[(int)(end.Y * nMapHeight + end.X)];
    Solve_AStar(t_map);
    return true;
}

bool BomberAI::posIsOnMap(vector2df pos, GameMap *t_map)
{
    if (pos.X <= 0 || (pos.X + 1) >= t_map->getSize().X)
        return false;
    if (pos.Y <= 0 || (pos.Y + 1) >= t_map->getSize().Y)
        return false;
    return true;
}

bool BomberAI::posIsWalkable(vector2df pos, GameMap *t_map)
{
    if (!posIsOnMap(pos, t_map))
        return false;
    if (t_map->getMap()[pos.Y][pos.X] == '1' || t_map->getMap()[pos.Y][pos.X] == '2')
        return false;
    return true;
}

BomberAI::BomberAI(irr::IrrlichtDevice *t_device)
{
	std::cerr << "Creating player character..." << std::endl;
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
		m_node->setMaterialTexture(
			0, t_device->getVideoDriver()->getTexture("./media/sydney.bmp"));
		m_node->setScale(vector3df(10, 10, 10));
	}
	m_then = t_device->getTimer()->getTime();
}

BomberAI::~BomberAI()
{
}

size_t BomberAI::getDist(irr::core::vector3df aPos, irr::core::vector3df bPos)
{
    return (aPos - bPos).getLength();
}

IPlayer *BomberAI::getClosestPlayer(std::vector<IPlayer*> players)
{
    size_t resDist = 0;
    size_t plDist = 0;
    size_t closestPlIndex = 0;
    int i = 0;

    if (players.empty())
        return nullptr;
    for (; i < players.size(); ++i) {
        if (this == players[i])
            continue;
        plDist = getDist(getPosition(), players[i]->getPosition());
        if (plDist < resDist || resDist == 0) {
            resDist = plDist;
            closestPlIndex = i;
        }
    }
    return players[closestPlIndex];
}

/*
irr::core::vector3df BomberAI::getPosInDir(irr::core::vector3df plPos, size_t dir)
{
    irr::core::vector3df delta;

    switch (dir) {
        case 0:
            delta.X = 1;
            break;
        case 1:
            delta.Z = 1;
            break;
        case 2:
            delta.X = -1;
            break;
        case 3:
            delta.Z = -1;
            break;
    }
    return (GameMap::getCoords(plPos) + delta);
}

char BomberAI::getBlockInDir(GameMap *t_map, irr::core::vector3df plPos, size_t dir)
{
    int i = 0;
    irr::core::vector3df blockPos;
    IGameBlock *resBlock;

    blockPos = getPosInDir(plPos, dir);
    std::cout << "block in Pos = (" << blockPos.X << ", "  << blockPos.Z << ")\n";
    return (t_map->getMap()[blockPos.Z][blockPos.X]);
}
*/

bool BomberAI::isInBombRange(GameMap *t_map, vector2df testPos, vector2df *supPos)
{
    if (supPos != nullptr)
        if (testPos.X == (*supPos).X || testPos.Y == (*supPos).Y)
            return true;
    for (int i = 0; i < bombsPos.size(); ++i)
        if (testPos.X == bombsPos[i].X || testPos.Y == bombsPos[i].Y || !posIsWalkable(testPos, t_map))
            return true;
    return false;
}

vector2df *BomberAI::newHidingSpot(GameMap *t_map, vector2df *supPos)
{
    int checkBox = 0;
    int level = 1;
    int incrementer = 1;
    vector2df *testPos;

    testPos->X = GameMap::getCoords(getPosition()).X;
    testPos->Y = GameMap::getCoords(getPosition()).Z;

    while (isInBombRange(t_map, (*testPos), supPos)) {
        if (incrementer == 0) {
            if (checkBox == 3) {
                checkBox = 0;
                level += 1;
            } else
                checkBox += 1;
            incrementer = level;
        }
        switch (checkBox) {
            case 0:
                testPos->X += 1;
                break;
            case 1:
                testPos->Y += 1;
                break;
            case 2:
                testPos->X -= 1;
                break;
            case 3:
                testPos->Y -= 1;
                break;
        }
        if (!posIsOnMap((*testPos), t_map))
            return nullptr;
        incrementer -= 1;
    }
    return (testPos);
}
bool updateBombs(std::vector<Bomb *> b, IrrlichtDevice *device, int onScreen, GameMap *map, int o)
{
    o = o;
    time_t now = time(0);
	bool k = false;

    for (int i = 0; i < onScreen; i++)
    {
		if (!b[i])
			return false;
		if (now != b[i]->getStartTime()) {
				b[i]->setCurrentTime(now);
			if ((b[i]->getCurrentTime() - b[i]->getStartTime()) >= 2 && b[i]->getState() == STATE::EXPLOSE)
				b[i]->setState(STATE::ERASE);
        	if (((b[i]->getCurrentTime() - b[i]->getStartTime()) >= 2) &&
            (b[i]->getState() != STATE::EXPLOSE)) {
            b[i]->loadExplosion(device);
            b[i]->setState(STATE::EXPLOSE);
			map->explodeWall(b[i]->getPosition(), b[i]->getRadius());
            k = true;
        	}
			if ((b[i]->getState() == STATE::ERASE)) { 
				b[i]->clearExplosion();
				std::cout << "clear func" << std::endl;
				b.erase(b.begin() + i);
			}
		}
        /* if (now - b[i]->.getTime() >= 3)
            _bombs.erase(_bombs.begin() + i);*/
    }
    return (k);
}
// WHERE THE AI IS CODED
int BomberAI::pollEvents(irr::IrrlichtDevice* t_device, EventReceiver receiver, GameMap* t_map, std::vector<IPlayer*> t_players)
{
    (void) receiver;
    IPlayer *closestPl = getClosestPlayer(t_players);
    int nMapHeight = t_map->getSize().Y;
    int tmp = 256;
    vector2df *tmPos;
    vector2df curPos;
    static vector2df nextPos(-1);
    static vector2df oldGoal;
    bool k = false;

    if (m_onScreen > 0) {
		m_onScreen -= (k = updateBombs(_bombs, t_device, m_onScreen, t_map, 0)? 1 : 0);
		m_avail += (k)? 1 : 0;
	}
    if (!m_isSetUp)
        setUpNodes(t_map);
    if (closestPl != nullptr)
        tmp = getDist(closestPl->getPosition(), getPosition());
    if ((tmp / 255) < (1 + m_fire)) {
        std::cout << "bot drop bomb\n";
	    processBombs(t_device, t_map);
        // goto HIDING SPOT
    } else {
        curPos.X = GameMap::getCoords(getPosition()).X;
        curPos.Y = GameMap::getCoords(getPosition()).Z;

        if (goal != oldGoal) {
            oldGoal = goal;
            findPath(t_map, goal, curPos);
        }
        if (curPos == nextPos || nextPos.X == -1) {
            nextPos.X = nodes[(int)(curPos.Y * nMapHeight + curPos.X)].parent->x;
            nextPos.Y = nodes[(int)(curPos.Y * nMapHeight + curPos.X)].parent->y;
        }
        if (t_map->getMap()[nextPos.Y][nextPos.X] == '2') {
            if (/*can drop bomb &&*/ (tmPos = newHidingSpot(t_map, &curPos)) != nullptr)
                processBombs(t_device, t_map);
            else if ((tmPos = newHidingSpot(t_map)) != nullptr)
                goal = (*tmPos);
        }
      /*if (bomb explode)
            bombsPos.pop(bomb that exploded) */
        if (bombsPos.empty()) {
            goal.X = GameMap::getCoords(closestPl->getPosition()).X;
            goal.Y = GameMap::getCoords(closestPl->getPosition()).Z;
        }
    }
    processMoves(t_device, t_map);
    return 0;
}

int BomberAI::pickup(E_PLAYER_PICKUP t_pickup)
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

void BomberAI::setSpeed(size_t t_speed)
{
	m_MAX_SPEED /= m_speed;
    m_ACCELERATION /= m_speed;
    m_speed = t_speed;
    m_MAX_SPEED *= m_speed;
    m_ACCELERATION *= m_speed;
}

void BomberAI::setPosition(irr::core::vector3df t_pos)
{
	m_node->setPosition(t_pos);
}

E_PLAYER_ACTION_ERROR BomberAI::processMoves(irr::IrrlichtDevice* t_device, GameMap *t_map)
{
    if (!m_isSetUp)
        return EPERR_PATHFIND;

	const irr::u32 now = t_device->getTimer()->getTime();
	const irr::f32 frameDeltaTime = (f32) (now - m_then) / 1000.f;
	static irr::core::vector3df playerVelocity (0, 0, 0);
    static bool isHiding = false;
    vector2df curPos;
    vector2df nextPos;
    int nMapHeight = t_map->getSize().Y;

    m_then = now;

    curPos.X = GameMap::getCoords(getPosition()).X;
    curPos.Y = GameMap::getCoords(getPosition()).Z;

    nextPos.X = nodes[(int)(curPos.Y * nMapHeight + curPos.X)].parent->x;
    nextPos.Y = nodes[(int)(curPos.Y * nMapHeight + curPos.X)].parent->y;

    movePlayer(playerVelocity, (nextPos - curPos), frameDeltaTime);

    /*
    if (isHiding) {
        // wait for bomb to explode;
        // then : isHiding = false;
        processBombs(t_device, t_map); // just for error handling;
    } else if (t_map->getMap()[nextPos.Y][nextPos.X] == '2') {
        // isHiding = true;
        processBombs(t_device, t_map);
        // pose bombe;
        // cache toi;
    } else
    */

	m_node->setPosition(m_node->getPosition() + playerVelocity);
	return EPERR_SUCCESS;
}

void BomberAI::movePlayer(vector3df& playerVelocity, vector2df dir, f32 frameDeltaTime)
{
	if (dir.X >= 1) {
		playerVelocity.X += m_ACCELERATION * frameDeltaTime;
		playerVelocity.X = playerVelocity.X > m_MAX_SPEED ? m_MAX_SPEED : playerVelocity.X;
	} else if (dir.X <= -1) {
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

    if (dir.Y >= 1) {
		playerVelocity.Z += m_ACCELERATION * frameDeltaTime;
		playerVelocity.Z = playerVelocity.Z > m_MAX_SPEED ? m_MAX_SPEED : playerVelocity.Z;
	} else if (dir.Y <= -1) {
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

E_PLAYER_ACTION_ERROR BomberAI::processBombs(irr::IrrlichtDevice* t_device, GameMap* t_map)
{
	irr::core::vector2df bombPos;
	bombPos.X = t_map->positionForBomb(m_node->getPosition()).X;
	bombPos.Y = t_map->positionForBomb(m_node->getPosition()).Z;
    bombsPos.push_back(bombPos);

    m_onScreen += 1;
	m_avail -= 1;
	Bomb *b = new Bomb(m_node->getPosition(), t_device, m_fire);
	_bombs.push_back(b);
    /*
	if (t_receiver.IsKeyDown(m_keyBindings[4])) {
		new Bomb (bombPos, t_device->getSceneManager(),
		t_device->getVideoDriver(), t_device, m_fire);
		std::cerr << "Bomb dropped" << std::endl;
	}
    */

	return EPERR_SUCCESS;
}
