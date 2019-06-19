#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

typedef enum EntityType { NPC, PLAYER, EXIT, ROOM, ITEM };
typedef enum Direction { NORTH, EAST, SOUTH, WEST };

vector<string> Split(string str);
string DirectionToString(Direction dir);