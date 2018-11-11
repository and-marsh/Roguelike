#pragma once
#include "libtcod.h"
#include "Actor.h"
#include "Map.h"

class Engine {
public:
	enum GameStatus 
	{
		STARTUP,	 //first frame of the game
		IDLE,		 //no new turn. Redraw the same screen.
		NEW_TURN,	 //update the monsters position
		VICTORY,	 //the player won
		DEFEAT		 //the player was killed
	} gameStatus;

	TCODList<Actor *> actors;
	Actor *player;
	Map *map;
	int fovRadius;

	Engine();
	~Engine();
	void update();
	void render();
};

extern Engine engine;

