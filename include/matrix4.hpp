#pragma once

#include "matrix.hpp"
#include "vector.hpp"

namespace GLRT {
class Matrix4 : public Matrix<4, 4> {
   public:
	using Matrix<4, 4>::Matrix;

	static Matrix4 identity();
};
}  // namespace GLRT
