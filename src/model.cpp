#include "model.hpp"

#include <filesystem>
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

				auto i = std::stoi(index_token) - start_index;

				f.center += mesh.vertices[i].position;
				f.indices.push_back(i);
			}

			f.center /= f.indices.size();

			auto v1 = mesh.vertices[f.indices[0]].position;
			auto v2 = mesh.vertices[f.indices[1]].position;
			auto v3 = mesh.vertices[f.indices[2]].position;

			f.normal = (v2 - v1).cross(v3 - v1).normalized();

			mesh.faces.push_back(f);
		} else {
			// std::cout << "Unknown token: " << token << std::endl;
		}
	}
	meshes.push_back(mesh);

	return true;
}

Matrix4 Model::getTransform() const {
	return transform.getMatrix() * animation.GetTransform().getMatrix();
}

void Model::print() {
	std::cout << "Model: " << name << std::endl;
	std::cout << "Meshes: " << meshes.size() << std::endl;
	for(auto mesh : meshes) {
		mesh.print();
	}
}
}  // namespace GLRT
