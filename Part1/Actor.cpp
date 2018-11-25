//header include
#include "Actor.h"
//std includes
#include <iostream>
//libtcode include
#include "libtcod.h"
//local includes
#include "Engine.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////
// Actor class
////////////////////////////////////////////////////////////////////

Actor::Actor(int x, int y, int ch, const std::string& name, const TCODColor& col) :
	x(x),
	y(y),
	ch(ch),
	col(col),
	name(name),
	blocks(true),
	attacker(nullptr),
	destructible(nullptr),
	ai(nullptr)
{
}

void Actor::update()
{
	if (ai != nullptr) ai->update(this);
}

/*bool Actor::moveOrAttack(int x, int y)
{
	if (engine.map->isWall(x, y)) 
		return false;
	for (Actor **iterator = engine.actors.begin();
		iterator != engine.actors.end(); iterator++) 
	{
		Actor *actor = *iterator;
		if (actor->x == x && actor->y == y) 
		{
			std::cout << "The " << actor->name << 
				" laughs at your puny efforts to attack him!" << std::endl;
			return false;
		}
	}
	this->x = x;
	this->y = y;
	return true;
}*/

void Actor::render() const
{
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col);
}

////////////////////////////////////////////////////////////////////
// End Actor class
////////////////////////////////////////////////////////////////////
