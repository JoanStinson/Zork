#include "Player.h"

void Player::DescribeCurrentRoom() {
	cout << "You are now in " << this->location->GetName() << endl;
	GetLocation()->Look();
	cout << "In this room you will find: " << endl;
	if (Show(GetLocation()->contains, EntityType::ITEM) == 0) {
		cout << "no items" << endl;
	}
	Show(GetLocation()->contains, EntityType::NPC);
}

void Player::Inventory() {
	cout << "PLAYER INVENTORY: " << endl;
	cout << "You have " << Show(this->contains, EntityType::ITEM) << " items" << endl;
}

void Player::Look(string parameter) {

	bool looked = false;

	// Look at me
	if (parameter.compare("me") == 0) {
		this->Entity::Look();
		looked = true;
	}

	// Look at room
	if (!looked) {
		string currentRoomName = Globals::ToLowercase(location->GetName());
		if (currentRoomName.compare(parameter) == 0) {
			location->Look();
			looked = true;
		}
	}

	// Look at entities in the room
	if (!looked) {
		string entityName;

		for (Entity *e : location->contains) {

			// Si esta en la room y coincide nombre hacer look
			switch (e->GetType()) {
				case EntityType::NPC:
				case EntityType::EXIT:
				case EntityType::ITEM:
					entityName = Globals::ToLowercase(e->GetName());
					if (entityName.compare(parameter) == 0) {
						e->Look();
						looked = true;
					}
				break;
				default:
					break;
			}

		}
	}

	// Look at direction
	if (!looked) {
		Exit* exit = GetExitFromDirection(parameter);

		if (exit != NULL) {
			exit->Look();
			looked = true;
		}
	}

	if (!looked) {
		cerr << "Nothing relevant to look at " << parameter << endl;
	}

}

void Player::Go(string str) {

	bool moved = false;

	Exit *exit = GetExitFromDirection(str);
	if (exit != NULL) {
		if (exit->IsLocked()) {
			cout << str << " is locked" << endl;
		}
		else {
			cout << "Walking to " << str << "..." << endl;
			this->location = exit->GetDestination();
			DescribeCurrentRoom();
			moved = true;
		}
	}

	if (!moved)
		cout << "You can't go to " << str << endl;

}

void Player::Take(string str) {

	// Search for items
	Item* item = GetItemFromName(str, location->contains);

	if (item == NULL) {
		cout << "You can't take " << str << endl;
	}
	else {
		this->contains.push_back(item);
		this->location->contains.remove(item);
		cout << "You now have a " << str << endl;
	}
	
}

void Player::Drop(string str) {

	// Search for items
	Item* item = GetItemFromName(str);

	if (item == NULL) {
		cout << "You can't drop a " << str << endl;
	}
	else {
		if (GetHoldingItem() == item) {
			Unequip(str);
		}
		this->contains.remove(item);
		this->location->contains.push_back(item);
		cout << "You dropped a " << str << endl;
	}

}

void Player::Equip(string str) {

	// Search for items
	Item* item = GetItemFromName(str);

	if (item == NULL) {
		cout << "You can't equip a " << str << endl;
	}
	else {
		if (GetHoldingItem() != NULL)
			cout << "Switched " << GetHoldingItem()->GetName() << " for " << item->GetName() << endl;
		SetHoldingItem(item);
		cout << "Equipped a " << item->GetName() << endl;
	}

}

void Player::Unequip(string str) {

	// Search for items
	Item* item = GetItemFromName(str);

	if (item == NULL) {
		cout << "You can't unequip a " << str << endl;
	}
	else {
		if (GetHoldingItem() == item) {
			cout << "Unequipped a " << item->GetName() << endl;
			SetHoldingItem(NULL);
		}
		else {
			cout << "You are not holding a " << item->GetName() << endl;
		}
	}

}

void Player::Attack(string str) {

}

void Player::Lock(string str) {
	// Check if it's direction
	if (Globals::IsDirection(str)) {

		Direction* direction = Globals::StringToDirection(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == NULL) {
			cout << "There is no exit in " << str << endl;
		}
		else {

			if (!exit->IsLocked()) {

				// Search for items
				bool keyFound = false;
				for (Entity *e : this->contains) {
					if (e->GetType() == EntityType::ITEM) {
						Item* item = (Item*)e;

						// Check if we have a key (ONLY 1 KEY IN THE GAME)
						if (item->GetItemType() == ItemType::KEY) {
							keyFound = true;

							// Check if key is equipped
							if (GetHoldingItem() == item) {
								cout << str << " locked" << endl;
								exit->SetLocked(true);
							}
							else cout << "You are not holding a key" << endl;
							break;
						}
					}
				}

				if (!keyFound)
					cout << "You don't have a key to lock the exit" << endl;
			}
			else cout << str << " is already locked" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction (north, east, south, west)" << endl;
	}
}

void Player::Unlock(string str) {
	// Check if it's direction
	if (Globals::IsDirection(str)) {

		Direction* direction = Globals::StringToDirection(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == NULL) {
			cout << "There is no exit in " << str << endl;
		}
		else {

			if (exit->IsLocked()) {

				// Search for items
				bool keyFound = false;
				for (Entity *e : this->contains) {
					if (e->GetType() == EntityType::ITEM) {
						Item* item = (Item*)e;

						// Check if we have a key (ONLY 1 KEY IN THE GAME)
						if (item->GetItemType() == ItemType::KEY) {
							keyFound = true;

							// Check if key is equipped
							if (GetHoldingItem() == item) {
								cout << str << " unlocked" << endl;
								exit->SetLocked(false);
							}
							else cout << "You are not holding a key" << endl;
							break;
						}
					}
				}

				if (!keyFound)
					cout << "You don't have a key to unlock the exit" << endl;
			}
			else cout << str << " is already unlocked" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction (north, east, south, west)" << endl;
	}
}

void Player::Loot(string str) {
	// Mirar que sea un parametro valido y coincida con el nombre del npc
	// Si no tiene items, "nothing to loot" y sino, nos copiamos todo de su lista a nuestra y le borramos la suya
	bool foundNpc = false;

	for (Entity *e : location->contains) {

		// Si esta en la room y coincide nombre hacer look
		if (e->GetType() == EntityType::NPC) {

			class NPC* npc = (class NPC*)e;

			string npcName = Globals::ToLowercase(npc->GetName());
			if (npcName.compare(str) == 0) {
				foundNpc = true;

				if (!npc->contains.empty()) {
					this->contains.insert(this->contains.end(), npc->contains.begin(), npc->contains.end());
					cout << "You have looted from " << str << ":" << endl;
					Show(npc->contains, EntityType::ITEM);
					npc->contains.clear();
				}
				else cout << "Nothing to loot from " << str << endl;
				break;
			}
		}
	}

	if (!foundNpc)
		cout << "No NPCs found in this room" << endl;
}

Item * Player::GetHoldingItem() {
	return holdingItem;
}

void Player::SetHoldingItem(Item * item) {
	holdingItem = item;
}

Exit * Player::GetExitFromDirection(Direction dir) {
	Exit* exit = NULL;

	// Search for exits
	for (Entity *e : this->location->contains) {

		if (e->GetType() == EntityType::EXIT) {

			// Mirar cada tipo de comand NORTH, WEST, EAST, SOUTH sea igual al de la exit
			if (dir == ((Exit*)e)->GetDirection()) {
				exit = (Exit*)e;
				break;
			}
		}
	}

	return exit;

}
Exit * Player::GetExitFromDirection(string str) {
	return Globals::IsDirection(str) ? GetExitFromDirection(*Globals::StringToDirection(str)) : NULL;
}

Item * Player::GetItemFromName(string name) {
	return GetItemFromName(name, this->contains);
}

Item * Player::GetItemFromName(string name, list<Entity*> entities) {
	Item *item = NULL;

	// Search for items
	for (Entity *e : entities) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = Globals::ToLowercase(e->GetName());

			if (itemName.compare(name) == 0) {
				item = (Item*)e;
			}
		}
	}
	return item;
}