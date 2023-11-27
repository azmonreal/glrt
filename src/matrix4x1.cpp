#include "matrix4x1.hpp"

namespace GLRT {
Matrix4x1::Matrix4x1(const Vector<3>& v, double w) : Matrix<4, 1>{{v[0], v[1], v[2], w}} {}
Matrix4x1::Matrix4x1(const Vector<4>& v) : Matrix<4, 1>{{v[0], v[1], v[2], v[3]}} {}
}  // namespace GLRT
