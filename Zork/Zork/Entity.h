#pragma once
#include "Globals.h"

class Entity {

public:
	explicit Entity(EntityType type, string name, string description);
	virtual ~Entity();

	string GetName();
	string GetDescription();
	EntityType GetType();
	list<Entity*> contains;

	void Insert(Entity* entity);
	void Remove(Entity* entity);

	virtual Direction GetDirection() { return Direction(); }
	virtual void Update() = 0;
	virtual const void Look();

	bool operator == (const Entity& e) const { return type == e.type && name == e.name; }
	bool operator != (const Entity& e) const { return !operator==(e); }

protected:
	EntityType type;
	string name;
	string description;

private:
	static const map<EntityType, string> entitiesMap;
};