#pragma once
#include "Creature.h"

class NPC : public Creature {

public:
	NPC(string name, string description, string dialogue, Room* location) : Creature(EntityType::NPC, name, description, location) {
		this->dialogue = dialogue;
	}

	void Look();
	string GetDialogue() const;
	void SetDialogue(string& str);

private:
	string dialogue;
};
