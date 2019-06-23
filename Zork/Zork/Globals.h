#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

enum Direction { NORTH, EAST, SOUTH, WEST };

namespace Globals {
	 vector<string> split(string& str);
	 string dirToStr(const Direction& dir);
	 Direction* strToDir(const string& str);
	 string toLowercase(string str);
	 string toUppercase(string str);
	 bool isDir(const string& str);
	 string getCurrentTime();
};