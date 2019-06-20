#include "Globals.h"
#include "World.h"

int main() {

	cout << "Welcome to Zork!" << endl;

	World world;
	string input;

	while (true) {

		getline(cin, input);

		// Split string to words
		vector<string> words = Split(input);

		// Exit
		if (words.size() > 0 && (ToLowercase(words.at(0)).compare(ACTION_EXIT) == 0 || ToLowercase(words.at(0)).compare(ACTION_QUIT) == 0)) 
			break;

		// Parse command
		world.HandleInput(words);

	}
	cout << "Thanks for playing!" << endl;

	system("pause");
	return 0;
}