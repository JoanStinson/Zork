#pragma once
#include "Room.h"

class Creature : public Entity {

public:
	Creature(EntityType type, string name, string description, Room* location) : Entity(type, name, description) {
		this->location = location;
	}
	virtual void Update() = 0;

protected:
	Room* location;
};
