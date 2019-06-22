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

void Player::Look(const string& str) {

	bool looked = false;

	// Look at me
	if (str.compare("me") == 0) {
		this->Entity::Look();
		looked = true;
	}

	// Look at me
	if (str.compare("room") == 0) {
		DescribeCurrentRoom();
		looked = true;
	}

	// Look at room
	if (!looked) {
		string currentRoomName = Globals::toLowercase(location->GetName());
		if (currentRoomName.compare(str) == 0) {
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
					entityName = Globals::toLowercase(e->GetName());
					if (entityName.compare(str) == 0) {
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
		Exit* exit = GetExitFromDirection(str);

		if (exit != NULL) {
			exit->Look();
			looked = true;
		}
	}

	if (!looked) {
		cerr << "Nothing relevant to look at " << str << endl;
	}

}

void Player::Go(const string& str) {

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

void Player::Take(const string& str) {

	// Search for items
	Item* item = GetItemFromName(str, location->contains);

	if (item == NULL) {
		cout << "You can't take " << str << endl;
	}
	else {
		if (item->GetItemType() == ItemType::WEAPON) {

			Item* holder = GetItemFromType(ItemType::HOLDER);

			// Si no tenemos un holder, necesitamos un scabbard
			if (holder == NULL) {
				cout << "You need to have a holder to take this " << str << endl;
				return;
			}
			else {
				holder->Insert(item);
				item->SetParent(holder);
			}
		}

		this->contains.push_back(item);
		this->location->contains.remove(item);
		cout << "You now have a " << str << endl;
	}
	
}

void Player::Drop(const string& str) {

	// Search for items
	Item* item = GetItemFromName(str);

	if (item == NULL) {
		cout << "You can't drop a " << str << endl;
	}
	else {
		// Check if equipped
		if (GetHoldingItem() == item) {
			Unequip(str);
		}

		// Check for parent
		Entity* parent = item->GetParent();
		if (parent != NULL) {
			parent->Remove(item);
			item->SetParent(NULL);
		}

		// Check if childs
		for (Entity* child : item->contains) {
			this->contains.remove(child);
			this->location->contains.push_back(child);
			cout << "You dropped a " << child->GetName() << endl;
		}

		item->contains.clear();
		this->contains.remove(item);
		this->location->contains.push_back(item);
		cout << "You dropped a " << str << endl;
	}

}

void Player::Equip(const string& str) {

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

void Player::Unequip(const string& str) {

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

void Player::Attack(const string& str) {

}

void Player::Lock(const string& str) {
	// Check if it's direction
	if (Globals::isDir(str)) {

		Direction* direction = Globals::strToDir(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == NULL) {
			cout << "There is no exit in " << str << endl;
		}
		else {

			if (!exit->IsLocked()) {

				// Search for items
				Item* key = GetItemFromType(ItemType::KEY);

				if (key == NULL) {
					cout << "You don't have a key to lock the exit" << endl;
				}
				else {
					// Check if key is equipped
					if (key == GetHoldingItem()) {
						cout << str << " locked" << endl;
						exit->SetLocked(true);
					}
					else cout << "You are not holding a key" << endl;
				}					
			}
			else cout << str << " is already locked" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction (north, east, south, west)" << endl;
	}
}

void Player::Unlock(const string& str) {
	// Check if it's direction
	if (Globals::isDir(str)) {

		Direction* direction = Globals::strToDir(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == NULL) {
			cout << "There is no exit in " << str << endl;
		}
		else {

			if (exit->IsLocked()) {

				// Search for items
				Item* key = GetItemFromType(ItemType::KEY);

				if (key == NULL) {
					cout << "You don't have a key to unlock the exit" << endl;
				}
				else {
					// Check if key is equipped
					if (key == GetHoldingItem()) {
						cout << str << " unlocked" << endl;
						exit->SetLocked(false);
					}
					else cout << "You are not holding a key" << endl;
				}
			}
			else cout << str << " is already unlocked" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction (north, east, south, west)" << endl;
	}
}

void Player::Loot(const string& str) {
	// Mirar que sea un parametro valido y coincida con el nombre del npc
	// Si no tiene items, "nothing to loot" y sino, nos copiamos todo de su lista a nuestra y le borramos la suya
	bool foundNpc = false;

	for (Entity *e : location->contains) {

		// Si esta en la room y coincide nombre hacer look
		if (e->GetType() == EntityType::NPC) {

			class NPC* npc = (class NPC*)e;

			string npcName = Globals::toLowercase(npc->GetName());
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

Item * Player::GetHoldingItem() const {
	return holdingItem;
}

void Player::SetHoldingItem(Item * item) {
	holdingItem = item;
}

Exit * Player::GetExitFromDirection(const Direction& dir) const {
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
Exit * Player::GetExitFromDirection(const string& str) const {
	return Globals::isDir(str) ? GetExitFromDirection(*Globals::strToDir(str)) : NULL;
}

Item * Player::GetItemFromName(const string& name) const {
	return GetItemFromName(name, this->contains);
}

Item * Player::GetItemFromName(const string& name, const list<Entity*>& entities) const {
	Item *item = NULL;

	// Search for items
	for (Entity *e : entities) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = Globals::toLowercase(e->GetName());

			if (itemName.compare(name) == 0) {
				item = (Item*)e;
			}
		}
	}
	return item;
}

Item * Player::GetItemFromType(ItemType type) {
	Item *item = NULL;

	// Search for items
	for (Entity *e : this->contains) {

		if (e->GetType() == EntityType::ITEM && ((Item*)e)->GetItemType() == type) {

			//string itemName = Globals::toLowercase(e->GetName());

			//if (itemName.compare(name) == 0) {
			item = (Item*)e;
			break;
			//}
		}
	}
	return item;
}