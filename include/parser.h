#pragma once
#include <string>
#include <vector>
using namespace std;

class Parser {
	public:
	vector<string> cmds;
	vector<vector<string>> args;

	// constructors
	Parser();

	//other methods
	void parseInputFile(string filepath);
	vector<string> argumentsFromLine(string line);
	string commandFromLine(string line);
};