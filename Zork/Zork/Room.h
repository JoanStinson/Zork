#pragma once
#include "Entity.h"
#include "Item.h"

class Room : public Entity {
public:
	Room(string name, string description) : Entity(EntityType::ROOM, name, description) {}
	~Room();
	void Update(){}
	void InsertItem(Item *item);
	void RemoveItem(Item *item);
};
