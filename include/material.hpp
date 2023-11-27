#pragma once

#include "types.hpp"

namespace GLRT {
class Material {
   public:
	Material();
	~Material();

	Color ambient;
	Color diffuse;
	Color specular;
};
}  // namespace GLRT
