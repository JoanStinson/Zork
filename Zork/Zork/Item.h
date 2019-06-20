#pragma once
#include "Entity.h"

typedef enum ItemType {
	COMMON,
	KEY,
	WEAPON
};

class Item : public Entity {

public:
	Item(string name, string description, ItemType itemType = ItemType::COMMON) : Entity(EntityType::ITEM, name, description){
		this->itemType = itemType;
	}
	//Item(string name, string description) : Item(name, description, ItemType::COMMON) { }

	void Update() {}
	ItemType GetItemType();

private:
	ItemType itemType;

};
