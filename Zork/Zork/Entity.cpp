#include "Entity.h"

Entity::Entity(EntityType type, string name, string description) {
	this->type = type;
	this->name = name;
	this->description = description;
	this->parent = nullptr;
}

Entity::~Entity() {
	if (parent != nullptr)
		delete parent;
	for (Entity* e : contains)
		delete e;
	contains.clear();
}

string Entity::GetName() const {
	return name;
}

string Entity::GetDescription() const {
	return description;
}

EntityType Entity::GetType() const {
	return type;
}

Entity* Entity::GetParent() const {
	return parent;
}

void Entity::SetParent(Entity* parent) {
	this->parent = parent;
}

void Entity::Look() {
	cout << description << endl;
}

void Entity::Insert(Entity* entity) {
	contains.push_back(entity);
}

void Entity::Remove(Entity* entity) {
	contains.remove(entity);
}

int Entity::Show(list<Entity*>& entities, EntityType type) {
	int count = 0;

	// Search for items
	for (Entity* e : entities) {

		if (type == e->GetType()) {
			string itemName = Globals::toLowercase(e->GetName());
			cout << "- " << itemName << endl;
			count++;
		}
	}

	return count;
}