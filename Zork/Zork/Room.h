#pragma once
#include "Entity.h"
#include "Item.h"

class Room : public Entity {
public:
	Room(string name, string description) : Entity(EntityType::ROOM, name, description) {}

};
