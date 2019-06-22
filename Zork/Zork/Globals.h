#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

typedef enum Direction { NORTH, EAST, SOUTH, WEST };

class Globals {

public:
	static vector<string> Split(string str);
	static string DirectionToString(Direction dir);
	static Direction* StringToDirection(string str);
	static string ToLowercase(string str);
	static bool IsDirection(string str);
};