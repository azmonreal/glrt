#include "mesh.hpp"

#include <iostream>

namespace GLRT {
Mesh::Mesh() {}
Mesh::~Mesh() {}

void Mesh::print() {
	std::cout << "Mesh: " << name << std::endl;
	std::cout << "Vertices: " << vertices.size() << std::endl;
	for(auto& v : vertices) {
		std::cout << "  " << v.position[0] << " " << v.position[1] << " " << v.position[2] << std::endl;
	}

	std::cout << "Faces: " << faces.size() << std::endl;
	for(auto& f : faces) {
		std::cout << "  ";
		for(auto& i : f.indices) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}
}  // namespace GLRT
