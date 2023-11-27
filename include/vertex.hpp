#pragma once

#include <vector>

#include "types.hpp"

namespace GLRT {
class Vertex {
   public:
	Vertex();
	Vertex(Vector3 position);
	~Vertex();

	Vector3 position;
};
}  // namespace GLRT
