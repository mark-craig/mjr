#pragma once
#include <string>
#include <vector>
#include "scene.h"
using namespace std;

class Parser {
	public:
	vector<string> cmds;
	vector<vector<string>> args;

	// constructors
	Parser();

	//other methods
	Scene parseInputFile(string filepath);
	vector<string> parseline(string line);
	vector<Object*> parseObjFile(string filepath);
};
