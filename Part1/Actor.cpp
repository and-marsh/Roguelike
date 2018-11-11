#include <iostream>
#include "libtcod.hpp"
#include "Actor.h"
#include "Engine.h"
#include "Map.h"

Actor::Actor(int x, int y, int ch, const std::string name, const TCODColor & col) :
	x(x),
	y(y),
	ch(ch),
	name(name),
	col(col) {}

void Actor::update()
{
	std::cout << "The " << name << " growls!" << std::endl;
}

bool Actor::moveOrAttack(int x, int y)
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
}

void Actor::render() const
{
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col);
}
