#pragma once
#include "Globals.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "NPC.h"

#define ACTION_LOOK "look" 
#define ACTION_SEE "see" 

#define ACTION_GO "go"
#define ACTION_WALK "walk"

#define ACTION_TAKE "take"
#define ACTION_GRAB "grab"

#define ACTION_DROP "drop"
#define ACTION_LEAVE "leave"

#define ACTION_EQUIP "equip"
#define ACTION_ARM "arm"

#define ACTION_UNEQUIP "unequip"
#define ACTION_UNARM "unarm"

#define ACTION_ATTACK "attack"
#define ACTION_FIGHT "fight"

#define ACTION_LOCK "lock"
#define ACTION_CLOSE "close"

#define ACTION_UNLOCK "unlock"
#define ACTION_OPEN "open"

#define ACTION_LOOT "loot"
#define ACTION_STEAL "steal"

#define ACTION_EXIT "exit"
#define ACTION_QUIT "quit"

class World {
	
public:
	World();
	~World();

	void HandleInput(vector<string> &words);

private:
	void HandleAction(vector<string> &words);

	Player *player;
	vector<Entity*> entities;
};
