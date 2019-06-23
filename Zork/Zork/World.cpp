#include "World.h"

World::World() {

	// Create rooms
	Room* room1 = new Room("living room", "You are surrounded by medieval paintings.");
	Room* room2 = new Room("forest", "Tall trees are everywhere.");
	Room* room3 = new Room("tower", "You can see the clouds from up here.");
	Room* room4 = new Room("kitchen", "Smells like pizza in here.");
	Room* room5 = new Room("attic", "You are surrounded by ancient stuff.");
	Room* room6 = new Room("dungeon", "It's very dark you can't see anything.");

	// Create exits
	// Room 1
	Exit* exitR1toR2 = new Exit("door", ExitDescription(room2), Direction::EAST, room1, room2);
	Exit* exitR1toR3 = new Exit("stairs", ExitDescription(room3), Direction::WEST, room1, room3);
	exitR1toR3->SetLocked(true);
	Exit* exitR1toR6 = new Exit("door", ExitDescription(room6), Direction::NORTH, room1, room6);
	exitR1toR6->SetLocked(true);

	// Room 2
	Exit* exitR2toR1 = new Exit("window", ExitDescription(room1), Direction::WEST, room2, room1);

	// Room 3
	Exit* exitR3toR1 = new Exit("stairs", ExitDescription(room1), Direction::EAST, room3, room1);
	Exit* exitR3toR4 = new Exit("door", ExitDescription(room4), Direction::SOUTH, room3, room4);
	Exit* exitR3toR5 = new Exit("door", ExitDescription(room5), Direction::NORTH, room3, room5);

	// Room 4
	Exit* exitR4toR3 = new Exit("door", ExitDescription(room3), Direction::NORTH, room4, room3);

	// Room 5
	Exit* exitR5toR3 = new Exit("door", ExitDescription(room3), Direction::SOUTH, room5, room3);

	// Room 6
	Exit* exitR6toR1 = new Exit("door", ExitDescription(room1), Direction::SOUTH, room6, room1);

	// Create items
	Item* key = new Item("key", "It's a rusty old key, maybe it can open something.", ItemType::KEY);
	Item* rock = new Item("rock", "It's just a simple stupid rock.");
	Item* sword = new Item("sword", "A greek ancient sword used to kill monsters.", ItemType::WEAPON);
	Item* scabbard = new Item("scabbard", "An expensive scabbard used to hold weapons.", ItemType::HOLDER);

	// Create player
	player = new Player("Hero", "You are the mighty hero of this adventure!", room1);

	// Create npcs
	class NPC* ron = new class NPC("Ron", "He looks pretty fat.", "Stuck in this room? Check out the "+room2->GetName()+".", room1);
	class NPC* gilbert = new class NPC("Gilbert", "He's a very tall man.", "It's a dangerous place to go alone, be careful!", room3);

	Item* watch = new Item("watch", "The times is "+Globals::getCurrentTime());
	Item* book = new Item("book", "Ancient greek mythology, pretty interesting.");
	gilbert->Insert(watch);
	gilbert->Insert(book);

	// Create monsters
	Monster* goblin = new Monster("Goblin", "It's staring at you from the shadows, but you can't see it.", room6);

	// Add entities to Room 1
	room1->Insert(exitR1toR2);
	room1->Insert(exitR1toR3);
	room1->Insert(exitR1toR6);
	room1->Insert(rock);
	room1->Insert(ron);

	// Add entities to Room 2
	room2->Insert(exitR2toR1);
	room2->Insert(key);

	// Add entities to Room 3
	room3->Insert(exitR3toR1);
	room3->Insert(exitR3toR4);
	room3->Insert(exitR3toR5);
	room3->Insert(gilbert);

	// Add entities to Room 4
	room4->Insert(exitR4toR3);
	room4->Insert(sword);

	// Add entities to Room 5
	room5->Insert(exitR5toR3);
	room5->Insert(scabbard);

	// Add entities to Room 6
	room6->Insert(exitR6toR1);
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

	entities.push_back(ron);
	entities.push_back(gilbert);
	entities.push_back(goblin);

	entities.push_back(key);
	entities.push_back(rock);
	entities.push_back(sword);
	entities.push_back(scabbard);
	
	// Show init room
	player->DescribeCurrentRoom();
	gameOver = false;
}

World::~World() {
	for (Entity* e : entities)
		delete e;
	entities.clear();
	delete player;
}

void World::HandleInput(const vector<string>& words) {

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
	player = player;
}

bool World::IsGameOver() const {
	return gameOver;
}

void World::HandleAction(const vector<string>& words) {

	string actionName = Globals::toLowercase(words.at(0));
	string actionParameter = "";
	if (words.size() > 1) {
		actionParameter = Globals::toLowercase(words.at(1));
	}

	if (ACTION_INVENTORY == actionName) {
		player->Inventory();
	}
	else if (ACTION_LOOK == actionName || ACTION_SEE == actionName) {
		player->Look(actionParameter);
	}
	else if (ACTION_GO == actionName || ACTION_WALK == actionName) {
		player->Go(actionParameter);
	}
	else if (ACTION_TAKE == actionName || ACTION_GRAB == actionName) {
		player->Take(actionParameter);
	}
	else if (ACTION_DROP == actionName || ACTION_LEAVE == actionName) {
		player->Drop(actionParameter);
	}
	else if (ACTION_EQUIP == actionName || ACTION_ARM == actionName) {
		player->Equip(actionParameter);
	}
	else if (ACTION_UNEQUIP == actionName || ACTION_UNARM == actionName) {
		player->Unequip(actionParameter);
	}
	else if (ACTION_ATTACK == actionName || ACTION_FIGHT == actionName) {
		gameOver = player->Attack(actionParameter);
	}
	else if (ACTION_LOCK == actionName || ACTION_CLOSE == actionName) {
		player->Lock(actionParameter);
	}
	else if (ACTION_UNLOCK == actionName || ACTION_OPEN == actionName) {
		player->Unlock(actionParameter);
	}
	else if (ACTION_LOOT == actionName || ACTION_STEAL == actionName) {
		player->Loot(actionParameter);
	}
	else if (ACTION_TALK == actionName || ACTION_SPEAK == actionName) {
		player->Talk(actionParameter);
	}
	else if (ACTION_HELP == actionName) {
		ShowHelp();
	}
	else
		cerr << "Invalid action, please try again." << endl;
}

string World::ShowCommand(string str, string str2) const {
	string result = "- '" + Globals::toUppercase(str) + "'";
	if (str2.empty()) {
		result += " command";
	}
	else {
		result += " or '" + Globals::toUppercase(str2) + "'";
		result += " commands";
	}
	return result;
}

void World::ShowHelp() const {
	cout << "Action Commands:" << endl;
	cout << ShowCommand(ACTION_INVENTORY, "") << " shows all the items you have." << endl;
	cout << ShowCommand(ACTION_LOOK, ACTION_SEE) << " describe the object you specify." << endl;
	cout << ShowCommand(ACTION_GO, ACTION_WALK) << " move the player to a different room. The parameter must be a direction." << endl;
	cout << ShowCommand(ACTION_TAKE, ACTION_GRAB) << " put an item inside your inventory." << endl;
	cout << ShowCommand(ACTION_DROP, ACTION_LEAVE) << " drop the item from your inventory and place it in the current room." << endl;
	cout << ShowCommand(ACTION_EQUIP, ACTION_ARM) << " hold that item in your hand to use it." << endl;
	cout << ShowCommand(ACTION_UNEQUIP, ACTION_UNARM) << " unhold that item from your hand." << endl;
	cout << ShowCommand(ACTION_ATTACK, ACTION_FIGHT) << " attack a monster in the current room. You will need a weapon. The parameter must be a direction." << endl;
	cout << ShowCommand(ACTION_LOCK, ACTION_CLOSE) << " close an exit. You will need a key. The parameter must be a direction." << endl;
	cout << ShowCommand(ACTION_UNLOCK, ACTION_OPEN) << " opens an exit. You will need a key. The parameter must be a direction." << endl;
	cout << ShowCommand(ACTION_LOOT, ACTION_STEAL) << " takes all items from an NPC to your inventory." << endl;
	cout << ShowCommand(ACTION_TALK, ACTION_SPEAK) << " to have a little chit chat with an NPC." << endl;
	cout << ShowCommand(ACTION_EXIT, ACTION_QUIT) << " end the game." << endl;
}

string World::ExitDescription(Room* room) const {
	return "Exit to the " + room->GetName() + ".";
}
