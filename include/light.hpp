#pragma once

#include "transform.hpp"

namespace GLRT {
class Light {
   public:
	Light();
	~Light();

	Vector3 color;
	Vector3 position;
	Vector3 direction;
};
}  // namespace GLRT
