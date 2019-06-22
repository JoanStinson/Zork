#include "stdafx.h"
#include "CppUnitTest.h"
#include "fakeit.hpp"
using namespace fakeit;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WorldTest
{
	TEST_CLASS(WorldTest)
	{
	private:
		World *myworld;
	public:
		WorldTest() {

			myworld = new World();
		}

		TEST_METHOD(TestHandleInputNoWords) {
			vector<string> words;
			stringstream buffer;
			streambuf* sbuf = cerr.rdbuf();
			cerr.rdbuf(buffer.rdbuf());
			myworld->HandleInput(words);
			Assert::AreEqual(buffer.str().compare("ERROR: Type something!\n"), 0);
		}

		TEST_METHOD(TestHandleInputMoreThanTwoWords) {
			vector<string> words;
			words.push_back("This");
			words.push_back("are");
			words.push_back("words");
			stringstream buffer;
			streambuf* sbuf = cerr.rdbuf();
			cerr.rdbuf(buffer.rdbuf());
			myworld->HandleInput(words);
			Assert::AreEqual(buffer.str().compare("ERROR: Please type 2 words max!\n"), 0);
		}

		TEST_METHOD(TestHandleInputInvalidAction) {
			vector<string> words;
			words.push_back("Hello");
			stringstream buffer;
			streambuf* sbuf = cerr.rdbuf();
			cerr.rdbuf(buffer.rdbuf());
			myworld->HandleInput(words);
			Assert::AreEqual(buffer.str().compare("Invalid action, try again\n"), 0);
		}

		TEST_METHOD(TestHandleInputInventory) {
			vector<string> words;
			words.push_back("inventory");
			stringstream buffer;
			streambuf* sbuf = cerr.rdbuf();
			cerr.rdbuf(buffer.rdbuf());

			// SPY 
			Player *mockPlayer = new Player("Player", "", NULL);
			Mock<Player> spy(*mockPlayer);
			myworld->SetPlayer(mockPlayer);

			myworld->HandleInput(words);
			//TODO Verify
			//Verify(Method(mockPlayer, mockPlayer->Inventory));
		}

	};
}