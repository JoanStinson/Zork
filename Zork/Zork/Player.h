#pragma once
#include "Creature.h"
#include "Item.h"

class Player : public Creature {
public:
	Player(string name, string description, Room* location) : Creature(EntityType::PLAYER, name, description, location) {
	
	}
	~Player();
	void Update(){}
	void GrabItem(Item *item);
	void DropItem(Item *item);
};
