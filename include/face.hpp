#pragma once

#include <vector>
#include "types.hpp"
namespace GLRT {
class Face {
   public:
	Face();
	~Face();

	std::vector<int> indices;
	Vector3 normal;
	Vector3 center;
};
}  // namespace GLRT
