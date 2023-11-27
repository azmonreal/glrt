#pragma once

#include <memory>
#include <string>
#include <vector>

#include "animation.hpp"
#include "mesh.hpp"
#include "transform.hpp"

namespace GLRT {
class Model {
   public:
	Model();
	~Model();

	bool load(const std::string& path);

	Matrix4 getTransform() const;

	void print();

	std::string name;
	std::vector<Mesh> meshes;

	Animation animation;
	Transform transform;
};
}  // namespace GLRT
