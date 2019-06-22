#include "Globals.h"

vector<string> Globals::split(string& str) {
	vector<string> words;
	size_t pos = 0;
	string word;

	if (!str.empty()) {
		while ((pos = str.find(" ")) != string::npos) {
			word = str.substr(0, pos);
			words.push_back(word);
			str.erase(0, pos + 1);
		}

		if (!str.empty())
			words.push_back(str);
	}

	return words;
}

string Globals::dirToStr(const Direction& dir) {
	string result = "";

	switch (dir) {
		case NORTH:
			result = "north";
			break;
		case EAST:
			result = "east";
			break;
		case SOUTH:
			result = "south";
			break;
		case WEST:
			result = "west";
			break;
		default:
			break;
	}

	return result;
}

Direction* Globals::strToDir(const string& str) {
	Direction *result = NULL;

	if (str.compare("north") == 0)
		result = new Direction(Direction::NORTH);
	else if (str.compare("east") == 0)
		result = new Direction(Direction::EAST);
	else if (str.compare("south") == 0)
		result = new Direction(Direction::SOUTH);
	else if (str.compare("west") == 0)
		result = new Direction(Direction::WEST);

	return result;
}

string Globals::toLowercase(string str) {
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

bool Globals::isDir(const string& str) {
	return strToDir(str) != NULL;
}
