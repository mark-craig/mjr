#include "gtest/gtest.h"
#include "parser.h"
#include <vector>
#include <unistd.h>

//deprecated
// TEST(ParserTest, ParsesCommand) {
// 	Parser test = Parser();
// 	string line = "sph cx cy cz r\n";
// 	string command = test.commandFromLine(line);
// 	EXPECT_EQ(command, "sph");
// }

TEST(ParserTest, ParsesArguments) {
	Parser test = Parser();
	string line = "sph cx cy cz r\n";
	vector<string> arguments = test.parseline(line);
	EXPECT_EQ(arguments.size(), 5);
	EXPECT_EQ(arguments[0], "sph");
	EXPECT_EQ(arguments[1], "cx");
	EXPECT_EQ(arguments[2], "cy");
	EXPECT_EQ(arguments[3], "cz");
	EXPECT_EQ(arguments[4], "r");

}