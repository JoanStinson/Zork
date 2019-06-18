#include <iostream>
#include <vector>
#include <string>
#include "World.h"
using namespace std;

#define EXIT "exit"

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


int main() {

	cout << "Welcome to Zork" << endl;

	string input;
	bool isEnd = false;

	World world;

	while (!isEnd) {

		getline(cin, input);

		vector<string> words = Split(input);

		switch (words.size()) {
			case 0:
				cerr << "ERROR: Type something!" << endl;
				break;
			case 1:
				if (words.at(0).compare(EXIT) == 0) {
					cout << "Exited game" << endl;
					isEnd = true;
				}
				else {
					cout << "Invalid word" << endl;
				}
				break;
			case 2:
				//TODO
				cout << words.at(0) << " " << words.at(1) << endl;
				break;
			default:
				cerr << "ERROR: Please type 2 words max!" << endl;
				break;
		}

	}
	cout << "Thanks for playing!" << endl;

	return 0;
}