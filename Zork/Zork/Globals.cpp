#include "Globals.h"
#pragma warning(disable:4996)

namespace Globals {

	vector<string> split(string& str) {
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

	string dirToStr(const Direction& dir) {
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

	Direction* strToDir(const string& str) {
		Direction *result = nullptr;

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

	string toLowercase(string str) {
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}

	string toUppercase(string str) {
		std::transform(str.begin(), str.end(), str.begin(), toupper);
		return str;
	}

	bool isDir(const string& str) {
		return strToDir(str) != nullptr;
	}

	string getCurrentTime() {
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		string result = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
		return result;
	}
}

