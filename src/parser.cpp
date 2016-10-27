#include "parser.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "pystring.h"
#include "scene.h"
using namespace std;

Parser::Parser() {
}

Scene Parser::parseInputFile(string filepath) {
	ifstream f;
	f.open(filepath);
	if (f.bad()) {
		// for some reason the file fails to open
		string string = "Can not open file";
		cout<<string<<endl;
		throw;
	}
	Scene scene = Scene();
	Camera camera = Camera();
	Material material = Material();
	////Initialze an identity transformation
	// Transformation transformation = Transformation();
	string line; // each line we read out from file
	// cout << line << endl;
	while(!f.eof()) { // while we have not reached the end of the file
		getline(f, line);
		vector<string> parsed_line = parseline(line);
		// # will be comment lines
		if (strcmp(parsed_line[0].c_str(), "#") == 0) {
		// pass
		}
		// parse camera line
		else if (strcmp(parsed_line[0].c_str(), "cam") == 0) {
			// verify num args
			if (parsed_line.size() == 16) {
				string string = "Camera line improper args";
				cout<<string<<endl;
				throw;
			}
			camera = Camera(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
							stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]),
							stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]),
							stof(parsed_line[10]), stof(parsed_line[11]), stof(parsed_line[12]),
							stof(parsed_line[13]), stof(parsed_line[14]), stof(parsed_line[15]));
		} 
	}

	return scene;
}

vector<string> Parser::parseline(string line) {
	// given a line, return a vector containing all seperated elements
	vector<string> tokens;
	pystring::split(line, tokens);
	// tokens.erase(tokens.begin());
	return tokens;

}