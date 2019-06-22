#pragma once
#include "Creature.h"

class Monster : public Creature {

public:
	Monster(string name, string description, Room* location) : Creature(EntityType::MONSTER, name, description, location) {}

	//void Look();
};

