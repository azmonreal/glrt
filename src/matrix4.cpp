#include "matrix4.hpp"

namespace GLRT {
Matrix4::Matrix4(const Matrix<4, 4>& m) {
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) { m_data[i][j] = m[i][j]; }
	}
}

Matrix4 Matrix4::identity() {
	Matrix4 m;
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
	return m;
}
}  // namespace GLRT
