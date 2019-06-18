#pragma once
#include "Entity.h"
#include <vector>

class World {
	vector<Entity*> entities;
public:
	World();
	~World();
};
