#include "Entity.h"

Entity::Entity(EntityType type, string name, string description) {
	this->type = type;
	this->name = name;
	this->description = description;
	this->parent = NULL;
}

Entity::~Entity() {
	if (parent != NULL)
		delete parent;
	for (Entity *e : contains)
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

void Entity::Insert(Entity *entity) {
	contains.push_back(entity);
}

void Entity::Remove(Entity *entity) {
	contains.remove(entity);
}

void Entity::Look() {
	cout << name << ": " << description << endl;
}

int Entity::Show(list<Entity*>& entities, EntityType type) {
	int count = 0;

	// Search for items
	for (Entity *e : entities) {

		if (type == e->GetType()) {
			string itemName = Globals::toLowercase(e->GetName());
			cout << "- " << itemName << endl;
			count++;
		}
	}

	return count;
}

Entity * Entity::GetParent() {
	return parent;
}

void Entity::SetParent(Entity * parent) {
	this->parent = parent;
}
