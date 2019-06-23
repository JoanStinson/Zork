#include "Player.h"

void Player::DescribeCurrentRoom() {
	cout << "You are now in the " << location->GetName() << "." << endl;
	GetLocation()->Look();
	cout << "In this room you will find: " << endl;
	if (Show(GetLocation()->contains, EntityType::ITEM) == 0)
		cout << "No items." << endl;
	Show(GetLocation()->contains, EntityType::NPC);
	Show(GetLocation()->contains, EntityType::MONSTER);
}

void Player::Inventory() {
	cout << "Inventory: " << endl;
	cout << "You have " << Show(contains, EntityType::ITEM) << " items." << endl;
}

Item* Player::GetHoldingItem() const {
	return holdingItem;
}

void Player::SetHoldingItem(Item* item) {
	holdingItem = item;
}

void Player::Look(const string& str) {

	bool looked = false;

	// Look at me
	if ("me" == str) {
		Entity::Look();
		looked = true;
	}

	// Look at room
	if ("room" == str) {
		DescribeCurrentRoom();
		looked = true;
	}

	// Look at room using its name
	if (!looked) {
		string currentRoomName = Globals::toLowercase(location->GetName());
		if (currentRoomName == str) {
			location->Look();
			looked = true;
		}
	}

	// Look at entities in the room
	if (!looked) {
		string entityName;

		for (Entity *e : location->contains) {

			// If it's in the room and has the same name
			switch (e->GetType()) {
			case EntityType::NPC:
			case EntityType::EXIT:
			case EntityType::ITEM:
				entityName = Globals::toLowercase(e->GetName());
				if (entityName == str) {
					e->Look();
					looked = true;
				}
				break;
			default:
				break;
			}

		}
	}

	// Look at entities in your inventory
	if (!looked) {
		Item* item = GetEntityFromName<Item>(str, contains, EntityType::ITEM);

		if (item != nullptr) {
			item->Look();
			looked = true;
		}
	}

	// Look at direction
	if (!looked) {
		Exit* exit = GetExitFromDirection(str);

		if (exit != nullptr) {
			exit->Look();
			looked = true;
		}
	}

	if (!looked) {
		cerr << "Nothing relevant to look at " << str << "." << endl;
	}

}

void Player::Go(const string& str) {

	bool moved = false;

	Exit* exit = GetExitFromDirection(str);
	if (exit != nullptr) {
		if (exit->IsLocked()) {
			cout << str << " is locked." << endl;
		}
		else {
			cout << "Walking to " << str << "..." << endl;
			location = exit->GetDestination();
			DescribeCurrentRoom();
			moved = true;
		}
	}

	if (!moved)
		cout << "You can't go to " << str << "." << endl;

}

void Player::Take(const string& str) {

	// Search for items
	Item* item = GetEntityFromName<Item>(str, location->contains, EntityType::ITEM);

	if (item == nullptr) {
		cout << "You can't take " << str << "." << endl;
	}
	else {
		if (item->GetItemType() == ItemType::WEAPON) {

			Item* holder = GetItemFromType(ItemType::HOLDER);

			// If we don't have a holder, we need one (scabbard) 
			if (holder == nullptr) {
				cout << "You need to have a holder to take this " << str << "." << endl;
				return;
			}
			else {
				holder->Insert(item);
				item->SetParent(holder);
			}
		}

		contains.push_back(item);
		location->contains.remove(item);
		cout << "You now have a " << str << "." << endl;
	}

}

void Player::Drop(const string& str) {

	// Search for items
	Item* item = GetEntityFromName<Item>(str, contains, EntityType::ITEM);

	if (item == nullptr) {
		cout << "You can't drop a " << str << "." << endl;
	}
	else {
		// Check if equipped
		if (GetHoldingItem() == item) {
			Unequip(str);
		}

		// Check for parent
		Entity* parent = item->GetParent();
		if (parent != nullptr) {
			parent->Remove(item);
			item->SetParent(nullptr);
		}

		// Check if childs
		for (Entity* child : item->contains) {
			contains.remove(child);
			location->contains.push_back(child);
			cout << "You dropped a " << child->GetName() << "." << endl;
		}

		item->contains.clear();
		contains.remove(item);
		location->contains.push_back(item);
		cout << "You dropped a " << str << "." << endl;
	}

}

void Player::Equip(const string& str) {

	// Search for items
	Item* item = GetEntityFromName<Item>(str, contains, EntityType::ITEM);

	if (item == nullptr) {
		cout << "You can't equip a " << str << "." << endl;
	}
	else {
		if (GetHoldingItem() != nullptr)
			cout << "Switched " << GetHoldingItem()->GetName() << " for " << item->GetName() << "." << endl;
		SetHoldingItem(item);
		cout << "Equipped a " << item->GetName() << "." << endl;
	}

}

void Player::Unequip(const string& str) {

	// Search for items
	Item* item = GetEntityFromName<Item>(str, contains, EntityType::ITEM);

	if (item == nullptr) {
		cout << "You can't unequip a " << str << "." << endl;
	}
	else {
		if (GetHoldingItem() == item) {
			cout << "Unequipped a " << item->GetName() << "." << endl;
			SetHoldingItem(nullptr);
		}
		else {
			cout << "You are not holding a " << item->GetName() << "." << endl;
		}
	}

}

bool Player::Attack(const string& str) {
	bool gameOver = false;

	// Search monster
	Monster* monster = GetMonsterFromCurrentRoom();

	if (monster == nullptr) {
		cout << "Nothing to attack in this room." << endl;
	}
	else {

		if (str == Globals::toLowercase(monster->GetName())) {
			cout << "The room is dark, you don't see where the " << monster->GetName() << " is. Specify a direction to attack it." << endl;
		}
		else {

			// Check valid direction
			Direction* dir = Globals::strToDir(str);

			if (dir == nullptr) {
				cout << "You can't attack " << str << "." << endl;
			}
			else {

				Item* weapon = GetItemFromType(ItemType::WEAPON);

				if (weapon == nullptr) {
					cout << "You don't have a weapon to attack." << endl;
				}
				else {
					if (weapon == GetHoldingItem()) {
						monster->Attack(dir);
						if (monster->IsDead()) {
							cout << "CONGRATULATIONS! YOU BEAT THE GAME!" << endl;
							gameOver = true;
						}
					}
					else
						cout << "You need to equip a weapon to attack." << endl;
				}
			}
		}
	}

	return gameOver;
}

void Player::Lock(const string& str) {
	// Check if it's direction
	if (Globals::isDir(str)) {

		Direction* direction = Globals::strToDir(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == nullptr) {
			cout << "There is no exit in " << str << "." << endl;
		}
		else {

			if (!exit->IsLocked()) {

				// Search for items
				Item* key = GetItemFromType(ItemType::KEY);

				if (key == nullptr) {
					cout << "You don't have a key to lock the exit." << endl;
				}
				else {
					// Check if key is equipped
					if (key == GetHoldingItem()) {
						cout << str << " locked." << endl;
						exit->SetLocked(true);
					}
					else cout << "You are not holding a key." << endl;
				}
			}
			else cout << str << " is already locked!" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction." << endl;
	}
}

void Player::Unlock(const string& str) {
	// Check if it's direction
	if (Globals::isDir(str)) {

		Direction* direction = Globals::strToDir(str);
		Exit* exit = GetExitFromDirection(str);

		if (exit == nullptr) {
			cout << "There is no exit in " << str << "." << endl;
		}
		else {

			if (exit->IsLocked()) {

				// Search for items
				Item* key = GetItemFromType(ItemType::KEY);

				if (key == nullptr) {
					cout << "You don't have a key to unlock the exit." << endl;
				}
				else {
					// Check if key is equipped
					if (key == GetHoldingItem()) {
						cout << str << " unlocked." << endl;
						exit->SetLocked(false);
					}
					else cout << "You are not holding a key." << endl;
				}
			}
			else cout << str << " is already unlocked!" << endl;
		}

	}
	else {
		cout << "Parameter must be a direction." << endl;
	}
}

void Player::Loot(const string& str) {
	bool foundNpc = false;

	for (Entity* e : location->contains) {

		// If it's in the room and it has the same name
		if (e->GetType() == EntityType::NPC) {

			class NPC* npc = (class NPC*)e;

			string npcName = Globals::toLowercase(npc->GetName());
			if (npcName == str) {
				foundNpc = true;

				if (!npc->contains.empty()) {
					contains.insert(contains.end(), npc->contains.begin(), npc->contains.end());
					cout << "You have looted from " << str << ":" << endl;
					Show(npc->contains, EntityType::ITEM);
					npc->contains.clear();
				}
				else cout << "Nothing to loot from " << str << "." << endl;
				break;
			}
		}
	}

	if (!foundNpc)
		cout << "You can't loot from " << str << "." << endl;
}

void Player::Talk(const string& str) {
	class NPC* npc = GetEntityFromName<class NPC>(str, location->contains, EntityType::NPC);

	if (npc == nullptr) {
		cout << "You can't talk to " << str << "." << endl;
	}
	else {
		cout << npc->GetDialogue() << endl;
	}
}

Exit* Player::GetExitFromDirection(const Direction& dir) const {
	Exit* exit = nullptr;

	// Search for exits
	for (Entity* e : location->contains) {

		if (e->GetType() == EntityType::EXIT) {

			// Look at each type of direction parameter (NORTH, WEST, EAST, SOUTH) 
			if (dir == ((Exit*)e)->GetDirection()) {
				exit = (Exit*)e;
				break;
			}
		}
	}

	return exit;

}

Exit* Player::GetExitFromDirection(const string& str) const {
	return Globals::isDir(str) ? GetExitFromDirection(*Globals::strToDir(str)) : nullptr;
}

template <class T>
T* Player::GetEntityFromName(const string& name, const list<Entity*>& entities, const EntityType type) const {
	T* entity = nullptr;

	// Search for entities
	for (Entity* e : entities) {

		if (e->GetType() == type) {

			string entityName = Globals::toLowercase(e->GetName());
			if (entityName == name) {
				entity = (T*)e;
				break;
			}
		}
	}

	return entity;
}

Item* Player::GetItemFromType(ItemType type) const {
	Item* item = nullptr;

	// Search for items
	for (Entity* e : contains) {

		if (e->GetType() == EntityType::ITEM && ((Item*)e)->GetItemType() == type) {
			item = (Item*)e;
			break;
		}
	}
	return item;
}

Monster* Player::GetMonsterFromCurrentRoom() const {
	Monster* monster = nullptr;

	// Search for entities
	for (Entity* e : location->contains) {

		if (e->GetType() == EntityType::MONSTER) {
			monster = (Monster*)e;
			break;
		}
	}

	return monster;
}
