#include "NPC.h"

void NPC::Look() {
	Entity::Look();
	cout << name << " has the following items:" << endl;
	if (Show(contains, EntityType::ITEM) == 0) {
		cout << "No items" << endl;
	}
}
