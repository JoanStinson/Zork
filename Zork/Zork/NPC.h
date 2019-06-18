#pragma once
#include "Creature.h"

class NPC : public Creature {
public:
	NPC(string name, string description, Room* location) : Creature(EntityType::NPC, name, description, location) {}
	~NPC();
	void Update(){}
};
