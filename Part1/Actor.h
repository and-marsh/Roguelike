#pragma once

#include <string>
#include "libtcod.h"

class Actor
{
public:
	int x, y; // position on map
	int ch; // ascii code
	TCODColor col; // color
	const std::string name; // the actor's name

	Actor(int x, int y, int ch, const std::string name, const TCODColor &col);
	void update();
	bool moveOrAttack(int x, int y);
	void render() const;
	~Actor() = default;
};

