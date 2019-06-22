#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GlobalsTest
{		
	TEST_CLASS(GlobalsTest)
	{
	public:
		
		TEST_METHOD(TestToLowercase) {
			Assert::AreEqual(Globals::ToLowercase("HELLO").compare("hello"), 0);
			Assert::AreEqual(Globals::ToLowercase("hello").compare("hello"), 0);
			Assert::AreEqual(Globals::ToLowercase("HeLlO").compare("hello"), 0);
		}
		TEST_METHOD(TestSplitTwoWords) {
			vector<std::string> aux = Globals::Split("HELLO WORLD");
			Assert::IsTrue(aux.size() == 2);
			Assert::AreEqual(aux.at(0).compare("HELLO"), 0);
			Assert::AreEqual(aux.at(1).compare("WORLD"), 0);
		}
		TEST_METHOD(TestSplitOneWord) {
			vector<std::string> aux = Globals::Split("HELLO");
			Assert::IsTrue(aux.size() == 1);
			Assert::AreEqual(aux.at(0).compare("HELLO"), 0);
		}
		TEST_METHOD(TestSplitEmpty) {
			vector<std::string> aux = Globals::Split("");
			Assert::IsTrue(aux.size() == 0);
		}
		TEST_METHOD(TestIsDirectionIsTrue) {
			Assert::IsTrue(Globals::IsDirection("north"));
			Assert::IsTrue(Globals::IsDirection("west"));
			Assert::IsTrue(Globals::IsDirection("south"));
			Assert::IsTrue(Globals::IsDirection("east"));
		}
		TEST_METHOD(TestIsDirectionIsFalse) {
			Assert::IsFalse(Globals::IsDirection("NORTH"));
			Assert::IsFalse(Globals::IsDirection("perep"));
			Assert::IsFalse(Globals::IsDirection(""));
		}
		TEST_METHOD(TestStringToDirectionValid) {
			Direction* dirN = Globals::StringToDirection("north");
			Direction* dirW = Globals::StringToDirection("west");
			Direction* dirS = Globals::StringToDirection("south");
			Direction* dirE = Globals::StringToDirection("east");
			Assert::IsTrue(*dirN == Direction::NORTH);
			Assert::IsTrue(*dirW == Direction::WEST);
			Assert::IsTrue(*dirS == Direction::SOUTH);
			Assert::IsTrue(*dirE == Direction::EAST);
		}
		TEST_METHOD(TestStringToDirectionNotValid) {
			Direction* dir = Globals::StringToDirection("");
			Assert::IsNull(dir);
		}
		TEST_METHOD(TestDirectionToStringValid) {
			std::string strN = Globals::DirectionToString(Direction::NORTH);
			std::string strW = Globals::DirectionToString(Direction::WEST);
			std::string strS = Globals::DirectionToString(Direction::SOUTH);
			std::string strE = Globals::DirectionToString(Direction::EAST);
			Assert::IsTrue(strN == "north");
			Assert::IsTrue(strW == "west");
			Assert::IsTrue(strS == "south");
			Assert::IsTrue(strE == "east");
		}

	};
}