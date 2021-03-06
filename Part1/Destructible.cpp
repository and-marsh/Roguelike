//header include
#include "Destructible.h"
//std includes
#include <iostream>
//local includes
#include "Engine.h"

////////////////////////////////////////////////////////////////////
// Destructible class
////////////////////////////////////////////////////////////////////

Destructible::Destructible(float maxHp, float defense, const std::string& corpseName) :
	maxHp(maxHp),
	hp(maxHp),
	defense(defense),
	corpseName(corpseName)
{
};

float Destructible::takeDamage(Actor* owner, float damage)
{
	damage -= defense;
	if (damage > 0)
	{
		hp -= damage;
		if (hp <= 0)
			die(owner);
	}
	else
		damage = 0;
	return damage;
}

void Destructible::die(Actor* owner)
{
	// transform the actor into a corpse!
	owner->ch = '%';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

////////////////////////////////////////////////////////////////////
// End Destructible class
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// MonsterDestructible class
////////////////////////////////////////////////////////////////////

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char* corpseName) :
	Destructible(maxHp, defense, corpseName)
{
}

void MonsterDestructible::die(Actor* owner)
{
	// transform it into a nasty corpse! it doesn't block, can't be
	// attacked and doesn't move
	std::cout << owner->name << " is dead" << std::endl;
	Destructible::die(owner);
}

////////////////////////////////////////////////////////////////////
// end MonsterDestructible class
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// MonsterDestructible class
////////////////////////////////////////////////////////////////////

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char* corpseName) :
	Destructible(maxHp, defense, corpseName)
{
}

void PlayerDestructible::die(Actor* owner)
{
	std::cout << "You died!" << std::endl;
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}

////////////////////////////////////////////////////////////////////
// MonsterDestructible class
////////////////////////////////////////////////////////////////////
