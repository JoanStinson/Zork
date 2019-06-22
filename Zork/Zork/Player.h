#pragma once
#include "Globals.h"
#include "Creature.h"
#include "Exit.h"
#include "NPC.h"

class Player : public Creature {

public:
	Player(string name, string description, Room* location) : Creature(EntityType::PLAYER, name, description, location) { 
		this->holdingItem = NULL;
	}

	void DescribeCurrentRoom();
	void Inventory();

	// Actions
	void Look(const string& str);
	void Go(const string& str);
	void Take(const string& str);
	void Drop(const string& str);
	void Equip(const string& str);
	void Unequip(const string& str);
	void Attack(const string& str);
	void Lock(const string& str);
	void Unlock(const string& str);
	void Loot(const string& str);

	Item* GetHoldingItem() const;
	void SetHoldingItem(Item* item);

private:
	Item* holdingItem;
	Exit* GetExitFromDirection(const Direction& dir) const;
	Exit* GetExitFromDirection(const string& str) const;
	Item* GetItemFromName(const string& name) const;
	Item* GetItemFromName(const string& name, const list<Entity*>& entities) const;

};
