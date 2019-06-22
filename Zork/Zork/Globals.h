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
	static vector<string> split(string& str);
	static string dirToStr(const Direction& dir);
	static Direction* strToDir(const string& str);
	static string toLowercase(string str);
	static bool isDir(const string& str);
};