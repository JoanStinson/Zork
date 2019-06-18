#include "Entity.h"

Entity::Entity(EntityType type, string name, string description) {
	this->type = type;
	this->name = name;
	this->description;
}

Entity::~Entity()
{
}

void Entity::Insert(Entity *entity) {
	entities.push_back(entity);
}

void Entity::Remove(Entity *entity) {
	entities.remove(entity);
}
