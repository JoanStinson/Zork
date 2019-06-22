#pragma once
#include "Globals.h"

typedef enum EntityType { NPC, PLAYER, EXIT, ROOM, ITEM, MONSTER };

class Entity {

public:
	explicit Entity(EntityType type, string name, string description);
	virtual ~Entity();

	string GetName() const;
	string GetDescription() const;
	EntityType GetType() const;
	
	virtual void Look();
	void Insert(Entity* entity);
	void Remove(Entity* entity);
	int Show(list<Entity*>& entities, EntityType type);

	list<Entity*> contains;
	Entity* parent;

	Entity* GetParent();
	void SetParent(Entity* parent);

	bool operator == (const Entity& e) const { return type == e.type && name == e.name; }
	bool operator != (const Entity& e) const { return !operator==(e); }

protected:
	EntityType type;
	string name;
	string description;

private:
	static const map<EntityType, string> entitiesMap;
};