#include "parser.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "pystring.h"
#include "scene.h"
#include <unordered_map>
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
			if (parsed_line.size() != 16) {
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
		// parse sphere line
		else if (strcmp(parsed_line[0].c_str(), "sph") == 0) {
			// verify num args
			if (parsed_line.size() != 5) {
				string string = "Sphere line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D position = Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Sphere object = Sphere(position, stof(parsed_line[4]));
			//for transformations
			//object.addTransformation(transformation)
			object.addMaterial(material);
			scene.addObject(&object);
		}
		// parse triangle line
		else if (strcmp(parsed_line[0].c_str(), "tri") == 0) {
			// verify num args
			if (parsed_line.size() != 10) {
				string string = "Triangle line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D a = Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Vector3D b = Vector3D(stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			Vector3D c = Vector3D(stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]));
			Triangle object = Triangle(a, b, c);
			//for transformations
			//object.addTransformation(transformation
			object.addMaterial(material);
			scene.addObject(&object);
		}
		// parse obj file
		else if (strcmp(parsed_line[0].c_str(), "obj") == 0) {
			// verify num args
			if (parsed_line.size() != 2) {
				string string = "No obj file with that name";
				cout<<string<<endl;
				throw;
			}
			vector<Object*> objects = parseObjFile(parsed_line[1]);
			int sizeofobjects = objects.size();
			for (int i = 0; i < sizeofobjects; i += 1) {
				Object * object = objects[i];
				object->addMaterial(material);
				scene.addObject(object);
			}

		}
		// parse point light
		else if (strcmp(parsed_line[0].c_str(), "ltp") == 0) {
			// verify num args
			if (parsed_line.size() != 7 or parsed_line.size() == 8) {
				string string = "Point light line improper args";
				cout<<string<<endl;
				throw;
			}
			int falloff = 0;
			if (parsed_line.size() != 8) falloff  = stoi(parsed_line[7]);
			// add falloff later.
			PointLight light = PointLight(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
										  stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]),
										  falloff);
			scene.addLight(&light);
		}
		// parse directional light
		else if (strcmp(parsed_line[0].c_str(), "ltd") == 0) {
			// verify num args
			if (parsed_line.size() != 7) {
				string string = "Directional light line improper args";
				cout<<string<<endl;
				throw;
			}
			DirectionalLight light = DirectionalLight(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
										  			  stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			scene.addLight(&light);
		}
		// parse ambient light
		else if (strcmp(parsed_line[0].c_str(), "lta") == 0) {
			// verify num args
			if (parsed_line.size() != 4) {
				string string = "Ambient light line improper args";
				cout<<string<<endl;
				throw;
			}
			// this might not work
			DirectionalLight light = DirectionalLight(0.0f, 0.0f, 0.0f, stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			scene.addLight(&light);
		}
		// parse ambient light
		else if (strcmp(parsed_line[0].c_str(), "mat") == 0) {
			// verify num args
			if (parsed_line.size() != 14) {
				string string = "Material line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D ka = Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Vector3D kd = Vector3D(stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			Vector3D ks = Vector3D(stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]));
			Vector3D kr = Vector3D(stof(parsed_line[11]), stof(parsed_line[12]), stof(parsed_line[13]));
			float sp = stof(parsed_line[10]);
			BRDF brdf = BRDF(ka, kd, ks, kr);
			material = Material(brdf, sp);
		}
		// handle transformations
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

vector<Object*> Parser::parseObjFile(string filepath) {
	unordered_map<int, Vector3D> vertices;
	vector<Object*> objects;
	ifstream f;
	f.open(filepath);
	if (f.bad()) {
		// for some reason the file fails to open
		string string = "Can not open file";
		cout<<string<<endl;
		throw;
	}
	////Initialze an identity transformation
	// Transformation transformation = Transformation();
	string line; // each line we read out from file
	// cout << line << endl;
	int index = 1;
	while(!f.eof()) { // while we have not reached the end of the file
		getline(f, line);
		vector<string> parsed_line = parseline(line);
		if (strcmp(parsed_line[0].c_str(), "v")) {
			if (parsed_line.size() != 4) {
				string string = "Vertice line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D position = Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			vertices[index] = position;
			index += 1;
		}
		if (strcmp(parsed_line[0].c_str(), "f")) {
			if (parsed_line.size() != 4) {
				string string = "Face line improper args";
				cout<<string<<endl;
				throw;
			}
			Triangle triangle = Triangle(vertices[stoi(parsed_line[1])],vertices[stoi(parsed_line[2])],vertices[stoi(parsed_line[3])]);
			objects.push_back(&triangle);
		}
	}
	return objects;
}