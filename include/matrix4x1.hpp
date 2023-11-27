#pragma once

#include "matrix.hpp"
#include "vector.hpp"

namespace GLRT {
class Matrix4x1 : public Matrix<4, 1> {
   public:
	using Matrix<4, 1>::Matrix;

	Matrix4x1(const Vector<3>& v, double);
	Matrix4x1(const Vector<4>& v);
};
}  // namespace GLRT
