#pragma once
#include "Globals.h"
#include "Room.h"

class Exit : public Entity {

public:
	Exit(string name, string description, Direction direction, Room* source, Room* destination) : Entity(EntityType::EXIT, name, description) {
		this->direction = direction;
		this->source = source;
		this->destination = destination;
		this->locked = false;
	}

	Direction GetDirection();
	Room* GetSource();
	Room* GetDestination();
	void SetLocked(bool locked);
	bool IsLocked();

private:
	Direction direction;
	Room* source;
	Room* destination;
	bool locked;

};
