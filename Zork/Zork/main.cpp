#include "Globals.h"
#include "World.h"
#include <ctime>
#include <cstdlib>

int main() {

	cout << "WELCOME TO ZORK!" << endl;
	srand(static_cast<unsigned int>(time(NULL)));

	World world;
	string input;

	while (!world.IsGameOver()) {

		// Get input
		getline(cin, input);

		// Split string to words
		vector<string> words = Globals::split(input);

		// Exit
		if (words.size() > 0 && (ACTION_EXIT == Globals::toLowercase(words.at(0)) || ACTION_QUIT == Globals::toLowercase(words.at(0))))
			break;

		// Parse command
		world.HandleInput(words);

	}

	cout << "Thanks for playing!" << endl;
	system("pause");
	return 0;
}