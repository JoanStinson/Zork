#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

typedef enum Direction { NORTH, EAST, SOUTH, WEST };

vector<string> Split(string str);
string DirectionToString(Direction dir);
Direction* StringToDirection(string str);
string ToLowercase(string str);
bool IsDirection(string str);