#pragma once

#include <vector>

#include "face.hpp"
#include "vertex.hpp"

namespace GLRT {
class Mesh {
   public:
	Mesh();
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<Face> faces;
};
}  // namespace GLRT
