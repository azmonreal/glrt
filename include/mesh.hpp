#pragma once

#include <string>
#include <vector>

#include "face.hpp"
#include "vertex.hpp"

namespace GLRT {
class Mesh {
   public:
	Mesh();
	~Mesh();

	void print();

	std::string name;
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
};
}  // namespace GLRT
