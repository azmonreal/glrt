#include "matrix4.hpp"

namespace GLRT {
Matrix4 Matrix4::identity() {
	Matrix4 m;
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
	return m;
}
}  // namespace GLRT
