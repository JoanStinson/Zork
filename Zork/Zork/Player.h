#pragma once
#include "Globals.h"
#include "Creature.h"
#include "Exit.h"

class Player : public Creature {

public:
	Player(string name, string description, Room* location) : Creature(EntityType::PLAYER, name, description, location) { 
		this->holdingItem = NULL;
	}

	void DescribeCurrentRoom();
	void Update(){}
	void Inventory();
	void Look(string str);
	void Go(string str);
	void Take(string str);
	void Drop(string str);
	void Equip(string str);
	void Unequip(string str);
	void Attack(string str);
	void Lock(string str);
	void Unlock(string str);
	void Loot(string str);

	Item* GetHoldingItem();
	void SetHoldingItem(Item* item);

private:
	Item* holdingItem;

};
