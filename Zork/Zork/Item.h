#pragma once
#include "Entity.h"

typedef enum ItemType {
	COMMON,
	KEY,
	WEAPON, 
	HOLDER
};

class Item : public Entity {

public:
	Item(string name, string description, ItemType itemType = ItemType::COMMON) : Entity(EntityType::ITEM, name, description){
		this->itemType = itemType;
	}

	ItemType GetItemType() const;

private:
	ItemType itemType;

};
