#pragma once

#include <vector>

#include "mesh.hpp"

namespace GLRT {
class Model {
   public:
	Model();
	~Model();

	std::vector<Mesh> meshes;
};
}  // namespace GLRT
