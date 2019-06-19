#include "Globals.h"

vector<string> Split(string str) {
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

string DirectionToString(Direction dir) {
	string result;

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