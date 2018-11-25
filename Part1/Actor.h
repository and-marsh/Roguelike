#pragma once
//std includes
#include <string>
//libtcod include
#include "libtcod.h"
//local includes
class Actor;
#include "Ai.h"
#include "Attacker.h"
#include "Destructible.h"

////////////////////////////////////////////////////////////////////
// Actor class
////////////////////////////////////////////////////////////////////

class Actor
{
public:
	int x, y; // position on map
	int ch; // ascii code
	TCODColor col; // color
	std::string name; // the actor's name
	bool blocks; // can we walk on this actor?
	Attacker* attacker; // something that deals damage
	Destructible* destructible; // something that can be damaged
	Ai* ai; // something self-updating

	Actor(int x, int y, int ch, const std::string& name, const TCODColor& col);
	void update();
	void render() const;
	~Actor() = default;
};

////////////////////////////////////////////////////////////////////
// End Actor class
////////////////////////////////////////////////////////////////////
