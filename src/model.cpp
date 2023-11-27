#include "model.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace GLRT {
Model::Model() {}
Model::~Model() {}

bool Model::load(const std::string& path) {
	std::ifstream file(path);

	if(!file.is_open()) {
		std::cout << "Could not open file: " << path << std::endl;
		return false;
	}

	meshes.clear();

	name = std::filesystem::path(path).filename().string();

	std::string line;

	Mesh mesh;
	int start_index = 1;

	while(std::getline(file, line)) {
		std::istringstream stream(line);
		std::string token;

		stream >> token;

		if(token == "o") {
			if(mesh.name != "") {
				meshes.push_back(mesh);
				start_index = mesh.vertices.size() + 1;
			}
			mesh = Mesh{};
			stream >> mesh.name;
		} else if(token == "v") {
			Vertex v;
			stream >> v.position[0] >> v.position[1] >> v.position[2];
			mesh.vertices.push_back(v);
		} else if(token == "f") {
			Face f;

			std::string index;
			while(stream >> index) {
				std::istringstream index_stream(index);
				std::string index_token;

				std::getline(index_stream, index_token, '/');
				f.indices.push_back(std::stoi(index_token) - start_index);
			}
			mesh.faces.push_back(f);
		} else {
			// std::cout << "Unknown token: " << token << std::endl;
		}
	}
	meshes.push_back(mesh);

	return true;
}

void Model::print() {
	std::cout << "Model: " << name << std::endl;
	std::cout << "Meshes: " << meshes.size() << std::endl;
	for(auto mesh : meshes) {
		mesh.print();
	}
}
}  // namespace GLRT
