#include "Player.h"

void Player::DescribeCurrentRoom() {
	cout << "You are now in " << this->location->GetName() << endl;
	GetLocation()->Look();
	cout << "In this room you will find: " << endl;
	if (ShowItems(GetLocation()->contains) == 0) {
		cout << "no items" << endl;
	}
}

void Player::Inventory() {
	cout << "PLAYER INVENTORY: " << endl;
	cout << "You have " << ShowItems(this->contains) << " items" << endl;
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
		string currentRoomName = ToLowercase(location->GetName());
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
					entityName = ToLowercase(e->GetName());
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
		for (Entity *e : location->contains) {

			if (e->GetType() == EntityType::EXIT){
				Exit *exit = (Exit*)e;
				// Mirar cada tipo de comand NORTH, WEST, EAST, SOUTH sea igual al de la exit
				if (DirectionToString(exit->GetDirection()) == parameter) {
					e->Look();
					looked = true;
				}
			}
		}
	}

	if (!looked) {
		cerr << "Nothing relevant to look at " << parameter << endl;
	}

}

void Player::Go(string str) {

	bool moved = false;

	// Search for exits
	for (Entity *e : location->contains) {

		if (e->GetType() == EntityType::EXIT) {
			Exit *exit = (Exit*)e;
			// Mirar cada tipo de comand NORTH, WEST, EAST, SOUTH sea igual al de la exit
			if (DirectionToString(exit->GetDirection()) == str) {

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
		}
	}

	if (!moved)
		cout << "You can't go to " << str << endl;

}

void Player::Take(string str) {
	Entity *temp = NULL;

	// Search for items
	for (Entity *e : location->contains) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = ToLowercase(e->GetName());

			if (itemName.compare(str) == 0) {
				temp = e;
				this->contains.push_back(e);
				cout << "You now have a " << itemName << endl;
			}
		}
	}

	if (temp == NULL) {
		cout << "You can't take " << str << endl;
	}
	else {
		this->location->contains.remove(temp);
	}
		
}

void Player::Drop(string str) {
	Entity *temp = NULL;

	// Search for items
	for (Entity *e : contains) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = ToLowercase(e->GetName());
			//TODO unequip item if equipped
			if (itemName.compare(str) == 0) {
				temp = e;

			}
		}
	}

	if (temp == NULL) {
		cout << "You can't drop a " << str << endl;
	}
	else {
		if (GetHoldingItem() == temp) {
			Unequip(str);
		}
		this->contains.remove(temp);
		this->location->contains.push_back(temp);
		cout << "You dropped a " << str << endl;
	}

}

void Player::Equip(string str) {
	Item *temp = NULL;

	// Search for items
	for (Entity *e : contains) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = ToLowercase(e->GetName());

			if (itemName.compare(str) == 0) {
				temp = (Item*)e;
				//this->location->contains.push_back(e);
				//cout << "You equipped a " << itemName << endl;
			}
		}
	}

	//TODO mirar si ya lo tengo equipado o grabbed
	if (temp == NULL) {
		cout << "You can't equip a " << str << endl;
	}
	else {
		if (GetHoldingItem() != NULL)
			cout << "Switched " << GetHoldingItem()->GetName() << " for " << temp->GetName() << endl;
		SetHoldingItem(temp);
		cout << "Equipped a " << temp->GetName() << endl;
	}
}

void Player::Unequip(string str) {
	Item *temp = NULL;

	// Search for items
	for (Entity *e : contains) {

		if (e->GetType() == EntityType::ITEM) {

			string itemName = ToLowercase(e->GetName());

			if (itemName.compare(str) == 0) {
				temp = (Item*)e;
				//this->location->contains.push_back(e);
				//cout << "You equipped a " << itemName << endl;
			}
		}
	}

	if (temp == NULL) {
		cout << "You can't unequip a " << str << endl;
	}
	else {
		if (GetHoldingItem() == temp) {
			cout << "Unequipped a " << temp->GetName() << endl;
			SetHoldingItem(NULL);
		}
		else {
			cout << "You are not holding a " << temp->GetName() << endl;
		}
	}
}

void Player::Attack(string str) {

}

void Player::Lock(string str) {

}

void Player::Unlock(string str) {

}

void Player::Loot(string str) {

}

Item * Player::GetHoldingItem() {
	return holdingItem;
}

void Player::SetHoldingItem(Item * item) {
	holdingItem = item;
}
