#pragma once
#include "Globals.h"

typedef enum EntityType { NPC, PLAYER, EXIT, ROOM, ITEM };

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

	virtual void Update() = 0;
	virtual const void Look();

	int ShowItems(list<Entity*> entities);

	bool operator == (const Entity& e) const { return type == e.type && name == e.name; }
	bool operator != (const Entity& e) const { return !operator==(e); }

protected:
	EntityType type;
	string name;
	string description;

private:
	static const map<EntityType, string> entitiesMap;
};