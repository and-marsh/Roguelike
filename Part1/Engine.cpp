//header include
#include "Engine.h"
//libtcod include
#include "libtcod.h"
//local includes
class Actor;
#include "Ai.h"
#include "Actor.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////
// Engine class
////////////////////////////////////////////////////////////////////

Engine::Engine(int screenWidth, int screenHeight) :
	gameStatus(STARTUP),
	fovRadius(10),
	screenWidth(screenWidth),
	screenHeight(screenHeight)
{
	TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial", false);
	player = new Actor(40, 25, '@', "player", TCODColor::white);
	player->destructible = new PlayerDestructible(30, 2, "your cadaver");
	player->attacker = new Attacker(5);
	player->ai = new PlayerAi();
	actors.push(player);
	map = new Map(screenWidth, screenHeight);
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete map;
}

void Engine::update()
{
	if (gameStatus == STARTUP) map->computeFov();
	gameStatus = IDLE;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, nullptr);
	player->update();
	if (gameStatus == NEW_TURN)
	{
		for (auto actor : actors)
		{
			if (actor != player)
			{
				actor->update();
			}
		}
	}
}

void Engine::render()
{
	TCODConsole::root->clear();
	// draw the map
	map->render();
	// draw the actors
	for (auto actor : actors)
	{
		if (actor != player && map->isInFov(actor->x, actor->y))
		{
			actor->render();
		}
	}
	player->render();
	// show the player's stats
	TCODConsole::root->printf(1, screenHeight - 2, "HP : %d/%d",
	                          static_cast<int>(player->destructible->hp),
	                          static_cast<int>(player->destructible->maxHp));
}

void Engine::sendToBack(Actor* actor)
{
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}

////////////////////////////////////////////////////////////////////
// End Engine class
////////////////////////////////////////////////////////////////////
