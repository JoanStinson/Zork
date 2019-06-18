#pragma once
#include <string>
#include <list>
#include "Entity.h"
using namespace std;

typedef enum EntityType {
	NPC, PLAYER, EXIT, ROOM, ITEM
};

class Entity {
private:
	EntityType type;
	string name;
	string description;
	list<Entity*> entities;
protected:
	void Insert(Entity* entity);
	void Remove(Entity* entity);
public:
	explicit Entity(EntityType type, string name, string description);
	~Entity();
	virtual void Update() = 0;
	bool operator == (const Entity& e) const { return type == e.type && name == e.name; }
	bool operator != (const Entity& e) const { return !operator==(e); }
};