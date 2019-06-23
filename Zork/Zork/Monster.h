#pragma once
#include "Creature.h"

class Monster : public Creature {

public:
	Monster(string name, string description, Room* location) : Creature(EntityType::MONSTER, name, description, location) {
		UpdateMonsterPosition();
		this->life = 3;
	}

	Direction GetDirection() const;
	void Attack(Direction* dir);
	bool IsDead() const;

private:
	void UpdateMonsterPosition();

	Direction position;
	int life;
};

