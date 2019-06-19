#pragma once
#include "Globals.h"
#include "Creature.h"

class Player : public Creature {

public:
	Player(string name, string description, Room* location) : Creature(EntityType::PLAYER, name, description, location) { }

	void Update(){}
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

};
