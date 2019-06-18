#pragma once
#include "Entity.h"
#include "Room.h"

typedef enum Direction {
	NORTH, EAST, SOUTH, WEST
};

class Exit : public Entity {
	Direction direction;
	Room* source;
	Room* destination;
	bool locked;
public:
	Exit(string name, string description, Direction direction, Room* source, Room* destination) : Entity(EntityType::EXIT, name, description) {
		this->direction = direction;
		this->source = source;
		this->destination;
		this->locked = false;
	}
	~Exit();
	void Update(){}
	void SetLocked(bool locked);
	bool IsLocked();
};
