#include "Entity.h"

Entity::Entity(EntityType type, string name, string description) {
	this->type = type;
	this->name = name;
	this->description = description;
}

Entity::~Entity() {
	for (Entity *e : contains)
		delete e;
	contains.clear();
}

string Entity::GetName() {
	return name;
}

string Entity::GetDescription() {
	return description;
}

EntityType Entity::GetType() {
	return type;
}

void Entity::Insert(Entity *entity) {
	contains.push_back(entity);
}

void Entity::Remove(Entity *entity) {
	contains.remove(entity);
}

const void Entity::Look() {
	cout << name << ": " << description << endl;
}

int Entity::ShowItems(list<Entity*> entities) {
	int count = 0;

	// Search for items
	for (Entity *e : entities) {

		if (e->GetType() == EntityType::ITEM) {
			string itemName = ToLowercase(e->GetName());
			cout << "- " << itemName << endl;
			count++;
		}
	}

	return count;
}
