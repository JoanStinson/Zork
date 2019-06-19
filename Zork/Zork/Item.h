#pragma once
#include "Entity.h"

class Item : public Entity {

public:
	Item(string name, string description) : Entity(EntityType::ITEM, name, description){}

	void Update() {}

};
