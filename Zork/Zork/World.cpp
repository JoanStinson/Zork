#include "World.h"
#include "Room.h"
#include "Player.h"
#include "Exit.h"
#include "NPC.h"

World::World() {

	// Create rooms
	Room *room1 = new Room("Black Room", "This is a black room.");
	Room *room2 = new Room("White Room", "This is a white room.");
	Room *room3 = new Room("Yellow Room", "This is a yellow room.");

	// Create player
	Player *player = new Player("Joan", "I am the player.", room1);

	// Create exits
	Exit *exitR1toR2 = new Exit("Exit to R2", "Exit to the white room.", Direction::EAST, room1, room2);
	Exit *exitR2toR1 = new Exit("Exit to R1", "Exit to the black room.", Direction::WEST, room2, room1);
	Exit *exitR1toR3 = new Exit("Exit to R3", "Exit to the yellow room.", Direction::WEST, room1, room3);
	exitR1toR3->SetLocked(true);
	Exit *exitR3toR1 = new Exit("Exit to R1", "Exit to the black room.", Direction::EAST, room3, room1);

	// Create items
	Item *key = new Item("Key", "This is a key.");
	room2->InsertItem(key);

	// Create NPC
	class NPC *npc = new class NPC("Pepito", "Buenos dias me llamo Pepito", room3);

	// Add entities
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(player);
	entities.push_back(exitR1toR2);
	entities.push_back(exitR2toR1);
	entities.push_back(exitR1toR3);
	entities.push_back(exitR3toR1);
	entities.push_back(key);

}

World::~World() {
	for (Entity *e : entities)
		delete e;
	entities.clear();
}
