#include "World.h"
#include "Monster.h"

World::World() {

	// Create rooms
	Room *room1 = new Room("BlackRoom", "This is a black room.");
	Room *room2 = new Room("WhiteRoom", "This is a white room.");
	Room *room3 = new Room("YellowRoom", "This is a yellow room.");
	Room *room4 = new Room("BlueRoom", "This is a blue room.");
	Room *room5 = new Room("RedRoom", "This is a red room.");
	Room *room6 = new Room("OrangeRoom", "This is a orange room.");

	// Create player
	this->player = new Player("Joan", "I am the player.", room1);

	// Create exits
	// Room 1
	Exit *exitR1toR2 = new Exit("Window", "Exit to the white room.", Direction::EAST, room1, room2);
	Exit *exitR1toR3 = new Exit("Door", "Exit to the yellow room.", Direction::WEST, room1, room3);
	exitR1toR3->SetLocked(true);
	Exit *exitR1toR6 = new Exit("Door", "Exit to the orange room.", Direction::NORTH, room1, room6);
	exitR1toR6->SetLocked(true);

	// Room 2
	Exit *exitR2toR1 = new Exit("Window", "Exit to the black room.", Direction::WEST, room2, room1);

	// Room 3
	Exit *exitR3toR1 = new Exit("Door", "Exit to the black room.", Direction::EAST, room3, room1);
	Exit *exitR3toR4 = new Exit("Door", "Exit to the blue room.", Direction::SOUTH, room3, room4);
	Exit *exitR3toR5 = new Exit("Door", "Exit to the red room.", Direction::NORTH, room3, room5);

	// Room 4
	Exit *exitR4toR3 = new Exit("Door", "Exit to the yellow room.", Direction::NORTH, room4, room3);

	// Room 5
	Exit *exitR5toR3 = new Exit("Door", "Exit to the yellow room.", Direction::SOUTH, room5, room3);

	// Room 6
	Exit *exitR6toR1 = new Exit("Door", "Exit to the black room.", Direction::SOUTH, room6, room1);

	// Create items
	Item *key = new Item("key", "This is a key.", ItemType::KEY);
	Item *rock = new Item("rock", "A simple rock.");
	Item *sword = new Item("sword", "A simple sword.", ItemType::WEAPON);
	Item *scabbard = new Item("scabbard", "A simple scabbard.", ItemType::HOLDER);

	// Create NPCs
	class NPC *aldeano = new class NPC("Aldeano", "Buenos dias me llamo Aldeano", room1);
	Item* watch = new Item("Watch", "This is a watch.");
	Item* book = new Item("Book", "This is a book");
	aldeano->Insert(watch);
	aldeano->Insert(book);
	class NPC *pepito = new class NPC("Pepito", "Buenos dias me llamo Pepito", room3);

	// Create monsters
	Monster* goblin = new Monster("Goblin", "I'm a horrible goblin.", room6);

	// Add entities to Room 1
	room1->Insert(exitR1toR2);
	room1->Insert(exitR1toR3);
	room1->Insert(exitR1toR6);
	room1->Insert(rock);
	room1->Insert(aldeano);

	// Add entities to Room 2
	room2->Insert(exitR2toR1);
	room2->Insert(key);

	// Add entities to Room 3
	room3->Insert(exitR3toR1);
	room3->Insert(exitR3toR4);
	room3->Insert(exitR3toR5);
	room3->Insert(pepito);

	// Add entities to Room 4
	room4->Insert(exitR4toR3);
	room4->Insert(sword);

	// Add entities to Room 5
	room5->Insert(exitR5toR3);
	room5->Insert(scabbard);

	// Add entities to Room 6
	room6->Insert(exitR5toR3);
	room6->Insert(goblin);

	// Add all entities to world
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);
	entities.push_back(room5);
	entities.push_back(room6);

	entities.push_back(exitR1toR2);
	entities.push_back(exitR1toR3);
	entities.push_back(exitR1toR6);
	entities.push_back(exitR2toR1);
	entities.push_back(exitR3toR1);
	entities.push_back(exitR3toR4);
	entities.push_back(exitR3toR5);
	entities.push_back(exitR4toR3);
	entities.push_back(exitR5toR3);
	entities.push_back(exitR6toR1);

	entities.push_back(this->player);
	entities.push_back(aldeano);
	entities.push_back(pepito);
	entities.push_back(goblin);

	entities.push_back(key);
	entities.push_back(rock);
	entities.push_back(sword);
	entities.push_back(scabbard);
	
	// Show init room
	this->player->DescribeCurrentRoom();

}

World::~World() {
	for (Entity *e : entities)
		delete e;
	entities.clear();
}

void World::HandleInput(const vector<string>& words) const {

	switch (words.size()) {
		case 0:
			cerr << "ERROR: Type something!" << endl;
			break;
		case 1:
		case 2:
			HandleAction(words);
			break;
		default:
			cerr << "ERROR: Please type 2 words max!" << endl;
			break;
	}
}

void World::SetPlayer(Player* player) {
	this->player = player;
}

void World::HandleAction(const vector<string>& words) const {

	string actionName = Globals::toLowercase(words.at(0));
	string actionParameter = "";
	if (words.size() > 1) {
		actionParameter = Globals::toLowercase(words.at(1));
	}

	if (ACTION_INVENTORY == actionName) {
		this->player->Inventory();
	}
	else if (ACTION_LOOK == actionName || ACTION_SEE == actionName) {
		this->player->Look(actionParameter);
	}
	else if (ACTION_GO == actionName || ACTION_WALK == actionName) {
		this->player->Go(actionParameter);
	}
	else if (ACTION_TAKE == actionName || ACTION_GRAB == actionName) {
		this->player->Take(actionParameter);
	}
	else if (ACTION_DROP == actionName || ACTION_LEAVE == actionName) {
		this->player->Drop(actionParameter);
	}
	else if (ACTION_EQUIP == actionName || ACTION_ARM == actionName) {
		this->player->Equip(actionParameter);
	}
	else if (ACTION_UNEQUIP == actionName || ACTION_UNARM == actionName) {
		this->player->Unequip(actionParameter);
	}
	else if (ACTION_ATTACK == actionName || ACTION_FIGHT == actionName) {
		this->player->Attack(actionParameter);
	}
	else if (ACTION_LOCK == actionName || ACTION_CLOSE == actionName) {
		this->player->Lock(actionParameter);
	}
	else if (ACTION_UNLOCK == actionName || ACTION_OPEN == actionName) {
		this->player->Unlock(actionParameter);
	}
	else if (ACTION_LOOT == actionName || ACTION_STEAL == actionName) {
		this->player->Loot(actionParameter);
	}
	else
		cerr << "Invalid action, try again" << endl;
}
