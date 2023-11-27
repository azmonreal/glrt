#pragma once

#include <memory>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "transform.hpp"

namespace GLRT {
class Model {
   public:
	Model();
	~Model();

	bool load(const std::string& path);
	void print();

	std::string name;
	std::vector<Mesh> meshes;
	Transform transform{};
};
}  // namespace GLRT
