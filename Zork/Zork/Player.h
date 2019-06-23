#pragma once
#include "Globals.h"
#include "Creature.h"
#include "Exit.h"
#include "NPC.h"
#include "Monster.h"

class Player : public Creature {

public:
	Player(string name, string description, Room* location) : Creature(EntityType::PLAYER, name, description, location) { 
		this->holdingItem = nullptr;
	}

	void DescribeCurrentRoom();
	void Inventory();
	Item* GetHoldingItem() const;
	void SetHoldingItem(Item* item);

	// Actions
	void Look(const string& str);
	void Go(const string& str);
	void Take(const string& str);
	void Drop(const string& str);
	void Equip(const string& str);
	void Unequip(const string& str);
	bool Attack(const string& str);
	void Lock(const string& str);
	void Unlock(const string& str);
	void Loot(const string& str);
	void Talk(const string& str);

private:
	Exit* GetExitFromDirection(const Direction& dir) const;
	Exit* GetExitFromDirection(const string& str) const;
	template <class T>
	T* GetEntityFromName(const string& name, const list<Entity*>& entities, const EntityType type) const;
	Item* GetItemFromType(ItemType type) const;
	Monster* GetMonsterFromCurrentRoom() const;

	Item* holdingItem;
};
