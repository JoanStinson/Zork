#include "Player.h"

void Player::Look(string parameter) {

	bool looked = false;

	// Look at me
	if (parameter.compare("me") == 0) {
		this->Entity::Look();
		looked = true;
	}

	// Look at room
	if (!looked) {
		if (location->GetName().compare(parameter) == 0) {
			location->Look();
			looked = true;
		}
	}

	// Look at entities in the room
	if (!looked) {
		for (Entity *e : location->contains) {

			// Si esta en la room y coincide nombre hacer look
			switch (e->GetType()) {
				case EntityType::NPC:
				case EntityType::EXIT:
				case EntityType::ITEM:
					if (e->GetName().compare(parameter) == 0) {
						e->Look();
						looked = true;
					}
				break;
			}

		}
	}

	// Look at direction
	if (!looked) {
		for (Entity *e : location->contains) {

			if (e->GetType() == EntityType::EXIT){

				// Mirar cada tipo de comand NORTH, WEST, EAST, SOUTH sea igual al de la exit
				if (DirectionToString(e->GetDirection()) == parameter) {
					e->Look();
					looked = true;
				}
			}
		}
	}

	if (!looked) {
		cerr << "Can't look at " << parameter << endl;
	}

}

void Player::Go(string str) {

}

void Player::Take(string str) {

}

void Player::Drop(string str) {

}

void Player::Equip(string str) {

}

void Player::Unequip(string str) {

}

void Player::Attack(string str) {

}

void Player::Lock(string str) {

}

void Player::Unlock(string str) {

}

void Player::Loot(string str) {

}
