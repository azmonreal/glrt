#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "animation.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "transform.hpp"

namespace GLRT {
class Model {
   public:
	Model();
	~Model();

	bool load(const std::string& path);
	bool load_materials(const std::string& path);

	Matrix4 getTransform() const;

	void print();

	std::string name;
	std::map<std::string, Mesh> meshes;
	std::map<std::string, Material> materials;

	Animation animation{};
	Transform transform{};
};
}  // namespace GLRT
