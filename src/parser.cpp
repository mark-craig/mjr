#include "parser.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "pystring.h"
#include "scene.h"
#include <unordered_map>
#include "transformation.h"
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
	Scene * scene = new Scene();

	Camera * camera = new Camera();

	Material * material = new Material();

	////Initialze an identity transformation
	Transformation * transformation = new Transformation();

	string line; // each line we read out from file
	// cout << line << endl;

	while(getline(f, line)) { // while we have not reached the end of the file
		vector<string> parsed_line = parseline(line);
		// # will be comment lines
		if (parsed_line.size() == 0) {
			continue;
		} else if (strcmp(parsed_line[0].c_str(), "#") == 0) {
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
			delete camera;
			camera = new Camera(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
							stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]),
							stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]),
							stof(parsed_line[10]), stof(parsed_line[11]), stof(parsed_line[12]),
							stof(parsed_line[13]), stof(parsed_line[14]), stof(parsed_line[15]));
			scene->addCamera(* camera);
		}
		// parse sphere line
		else if (strcmp(parsed_line[0].c_str(), "sph") == 0) {
			// verify num args
			if (parsed_line.size() != 5) {
				string string = "Sphere line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D * position = new Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Sphere * object = new Sphere(* position, stof(parsed_line[4]));
			//for transformations
			object->addMaterial(* material);
			object->addTransformation(* transformation);
			scene->addObject(object);
		}
		// parse triangle line
		else if (strcmp(parsed_line[0].c_str(), "tri") == 0) {
			// verify num args
			if (parsed_line.size() != 10) {
				string string = "Triangle line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D * a = new Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Vector3D * b = new Vector3D(stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			Vector3D * c = new Vector3D(stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]));
			Triangle * object = new Triangle(*a, *b, *c);
			//for transformations
			object->addMaterial(* material);
			object->addTransformation(* transformation);
			scene->addObject(object);
		}
		// parse obj file
		else if (strcmp(parsed_line[0].c_str(), "obj") == 0) {
			vector<string> quotes_split;
			pystring::rsplit(line, quotes_split, "\"");
			string objFilePath = quotes_split[1];
			cerr << objFilePath << endl;
			// // verify num args
			// if (parsed_line.size() != 2) {
			// 	string string = "No obj file with that name";
			// 	cout<<string<<endl;
			// 	throw;
			// }
			//cerr << "parsing obj file" << endl;
			unordered_map<int, Vector3D*> vertices;
			vector<Object*> objects;
			ifstream filename;
			filename.open(objFilePath);
			if (filename.bad()) {
				// for some reason the file fails to open
				string string = "Can not open file";
				cout<<string<<endl;
				throw;
			}
	
			string line2; // each line we read out from file
			int index = 1;
			while(getline(filename, line2)) { // while we have not reached the end of the file
				//cerr << "getting a line from obj file" << endl;
				vector<string> objLine = parseline(line2);
				if (objLine.size() == 0) {
					continue;
				}
				//cerr << objLine[0] << endl;
				if (strcmp(objLine[0].c_str(), "v") == 0) {
					if (objLine.size() != 4) {
						string string = "Vertice line improper args";
						cout<<string<<endl;
						throw;
					}
					Vector3D * position = new Vector3D(stof(objLine[1]), stof(objLine[2]), stof(objLine[3]));
					vertices[index] = position;
					index += 1;
				}
				if (strcmp(objLine[0].c_str(), "f") == 0) {
					if (objLine.size() != 4) {
						string string = "Face line improper args";
						cout<<string<<endl;
						throw;
					}
					//cerr << "creating a triangle" << endl;
					Object * triangle = new Triangle(* vertices[stoi(objLine[1])], * vertices[stoi(objLine[2])], * vertices[stoi(objLine[3])]);
					// Triangle * triangle = new Triangle(Vector3D(1, 0, 1), Vector3D(0, 1, 1), Vector3D(0, 0, 1));
					triangle->addMaterial(* material);
					triangle->addTransformation(* transformation);
					scene->addObject(triangle);
					//cerr << triangle->v1.x << triangle->v1.y << triangle->v1.z << "v1" << endl;
					//cerr << triangle->v2.x << triangle->v2.y << triangle->v2.z << "v2" << endl;
					//cerr << triangle->v3.x << triangle->v3.y << triangle->v3.z << "v3" << endl;
				}
			}
			// cerr << "done processing obj file" << endl;
			// int sizeofobjects = objects.size();
			// cerr << sizeofobjects << "objects" << endl;
			// for (int i = 0; i < sizeofobjects; i += 1) {
			// 	Object * object = objects[i];
			// 	object->addMaterial(* material);
			// 	object->addTransformation(* transformation);
			// 	scene->addObject(object);
			// }
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
			PointLight * light = new PointLight(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
										  stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]),
										  falloff);
			scene->addLight(light);
		}
		// parse directional light
		else if (strcmp(parsed_line[0].c_str(), "ltd") == 0) {
			// verify num args
			if (parsed_line.size() != 7) {
				string string = "Directional light line improper args";
				cout<<string<<endl;
				throw;
			}
			DirectionalLight * light = new DirectionalLight(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]),
										  			  stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			scene->addLight(light);
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
			DirectionalLight * light = new DirectionalLight(0.0f, 0.0f, 0.0f, stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			scene->addLight(light);
		}
		// parse material
		else if (strcmp(parsed_line[0].c_str(), "mat") == 0) {
			// verify num args
			if (parsed_line.size() != 14) {
				string string = "Material line improper args";
				cout<<string<<endl;
				throw;
			}
			Vector3D *ka = new Vector3D(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			Vector3D *kd = new Vector3D(stof(parsed_line[4]), stof(parsed_line[5]), stof(parsed_line[6]));
			Vector3D *ks = new Vector3D(stof(parsed_line[7]), stof(parsed_line[8]), stof(parsed_line[9]));
			Vector3D *kr = new Vector3D(stof(parsed_line[11]), stof(parsed_line[12]), stof(parsed_line[13]));
			float sp = stof(parsed_line[10]);
			BRDF * brdf = new BRDF(*ka, *kd, *ks, *kr);
			material = new Material(*brdf, sp);
		}
		// handle transformations
		else if (strcmp(parsed_line[0].c_str(), "xfr") == 0) {
			// verify num args
			if (parsed_line.size() != 4) {
				string string = "Rotation line improper args";
				cout<<string<<endl;
				throw;
			}
			Rotate * transform = new Rotate(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			transformation = new Transformation(* transformation, * transform);
		}
		else if (strcmp(parsed_line[0].c_str(), "xfs") == 0) {
			// verify num args
			if (parsed_line.size() != 4) {
				string string = "Scale line improper args";
				cout<<string<<endl;
				throw;
			}
			Scale * transform = new Scale(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			transformation = new Transformation( *transformation, * transform);
		}
		else if (strcmp(parsed_line[0].c_str(), "xft") == 0) {
			// verify num args
			if (parsed_line.size() != 4) {
				string string = "Translate line improper args";
				cout<<string<<endl;
				throw;
			}
			Translate * transform = new Translate(stof(parsed_line[1]), stof(parsed_line[2]), stof(parsed_line[3]));
			transformation = new Transformation(* transformation, * transform);
		}
		else if (strcmp(parsed_line[0].c_str(), "xfz") == 0) {
			// verify num args
			if (parsed_line.size() != 1) {
				string string = "Identity line improper args";
				cout<<string<<endl;
				throw;
			}
			transformation = new Transformation();
		}
	}
	return * scene;
}

vector<string> Parser::parseline(string line) {
	// given a line, return a vector containing all seperated elements
	vector<string> tokens;
	pystring::split(line, tokens);
	// tokens.erase(tokens.begin());
	return tokens;

}