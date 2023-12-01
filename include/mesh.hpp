#pragma once

#include <string>
#include <vector>

#include "animation.hpp"
#include "face.hpp"
#include "transform.hpp"
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
	std::string material;

	Animation animation{};
	Transform transform{};
};
}  // namespace GLRT
