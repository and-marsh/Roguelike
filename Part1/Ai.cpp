//header include
#include "Ai.h"
//std includes
#include <iostream>
//local includes
#include "Actor.h"
#include "Engine.h"

// how many turns the monster chases the player
// after losing his sight
static const int TRACKING_TURNS = 3;

////////////////////////////////////////////////////////////////////
// Ai class
////////////////////////////////////////////////////////////////////

//pure virtual class has no realization

////////////////////////////////////////////////////////////////////
// End Ai class
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// End PlayerAi  class
////////////////////////////////////////////////////////////////////

void PlayerAi::update(Actor* owner)
{
	if (owner->destructible != nullptr && owner->destructible->isDead())
	{
		return;
	}
	int dx = 0, dy = 0;
	switch (engine.lastKey.vk)
	{
	case TCODK_UP: dy = -1;
		break;
	case TCODK_DOWN: dy = 1;
		break;
	case TCODK_LEFT: dx = -1;
		break;
	case TCODK_RIGHT: dx = 1;
		break;
	default: break;
	}
	if (dx != 0 || dy != 0)
	{
		engine.gameStatus = Engine::NEW_TURN;
		if (moveOrAttack(owner, owner->x + dx, owner->y + dy))
		{
			engine.map->computeFov();
		}
	}
}

bool PlayerAi::moveOrAttack(Actor* owner, int targetx, int targety)
{
	if (engine.map->isWall(targetx, targety)) return false;
	// look for living actors to attack
	for (auto actor : engine.actors)
	{
		if (actor->destructible && !actor->destructible->isDead()
			&& actor->x == targetx && actor->y == targety)
		{
			owner->attacker->attack(owner, actor);
			return false;
		}
	}
	// look for corpses
	for (auto actor : engine.actors)
	{
		if (actor->destructible && actor->destructible->isDead()
			&& actor->x == targetx && actor->y == targety)
		{
			std::cout << "There's a" << actor->name << " here" << std::endl;
		}
	}
	owner->x = targetx;
	owner->y = targety;
	return true;
}

////////////////////////////////////////////////////////////////////
// End PlayerAi  class
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// MonsterAi  class
////////////////////////////////////////////////////////////////////

MonsterAi::MonsterAi() : moveCount(0)
{
}

void MonsterAi::update(Actor* owner)
{
	if (owner->destructible && owner->destructible->isDead())
	{
		return;
	}
	if (engine.map->isInFov(owner->x, owner->y))
	{
		// we can see the player. move towards him
		moveCount = TRACKING_TURNS;
	}
	else
	{
		moveCount--;
	}
	if (moveCount > 0)
	{
		moveOrAttack(owner, engine.player->x, engine.player->y);
	}
}

void MonsterAi::moveOrAttack(Actor* owner, int targetx, int targety)
{
	int dx = targetx - owner->x;
	int dy = targety - owner->y;
	int stepdx = (dx > 0 ? 1 : -1);
	int stepdy = (dy > 0 ? 1 : -1);
	float distance = sqrtf(dx * dx + dy * dy);
	if (distance >= 2)
	{
		dx = static_cast<int>(round(dx / distance));
		dy = static_cast<int>(round(dy / distance));
		if (engine.map->canWalk(owner->x + dx, owner->y + dy))
		{
			owner->x += dx;
			owner->y += dy;
		}
		else if (engine.map->canWalk(owner->x + stepdx, owner->y))
		{
			owner->x += stepdx;
		}
		else if (engine.map->canWalk(owner->x, owner->y + stepdy))
		{
			owner->y += stepdy;
		}
	}
	else if (owner->attacker)
	{
		owner->attacker->attack(owner, engine.player);
	}
}

////////////////////////////////////////////////////////////////////
// End MonsterAi  class
////////////////////////////////////////////////////////////////////
