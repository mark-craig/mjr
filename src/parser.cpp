#include "parser.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
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
	stringstream ss(line);
	vector<string> args = vector<string>();
	string arg;
	int i = 0;
	while(ss.good()) {
		if (i == 0) {
			continue;
		}
		arg = "";
		ss >> arg;
		args.push_back(arg);
		i++;
	}
	return args;

}

string Parser::commandFromLine(string line) {
	// given a line, return a vector containing the command
	stringstream ss(line);
	string cmd;
	ss >> cmd;
	return cmd;
}