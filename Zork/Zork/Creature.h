#pragma once
#include "Entity.h"
#include "Room.h"

class Creature : public Entity {
private:
	Room* location;
public:
	Creature(EntityType type, string name, string description, Room* location) : Entity(type, name, description) {
		this->location = location;
	}
	~Creature();
	virtual void Update() = 0;
};
