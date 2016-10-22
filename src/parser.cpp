#include "parser.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "pystring.h"
using namespace std;

Parser::Parser() {
}

void Parser::parseInputFile(string filepath) {
	ifstream f;
	f.open(filepath);
	if (f.bad()) {
		// for some reason the file fails to open
		return;
	}
	string line; // each line we read out from file
	// cout << line << endl;
	while(!f.eof()) { // while we have not reached the end of the file
		getline(f, line);
		// cout << line << endl;
		// clear out previous matches		
		cmds.push_back(commandFromLine(line));
		args.push_back(argumentsFromLine(line));
	}

	return;
}

vector<string> Parser::argumentsFromLine(string line) {
	// given a line, return a vector containing all the arguments
	vector<string> tokens;
	pystring::split(line, tokens);
	tokens.erase(tokens.begin());
	return tokens;

}

string Parser::commandFromLine(string line) {
	// given a line, return a vector containing the command
	vector<string> tokens;
	pystring::split(line, tokens);
	return tokens[0];
}