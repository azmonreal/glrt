#pragma once

#include "matrix4.hpp"
#include "types.hpp"

namespace GLRT {
class Transform {
   public:
	static Matrix4 translation_matrix(const Vector3& translation);
	static Matrix4 rotation_matrix(const Vector3& axis, double angle);
	static Matrix4 scale_matrix(const Vector3& scale);

	Transform();
	~Transform();

	void translate(const Vector3& translation);
	void rotate(const Vector3& rotation);
	void scale(const Vector3& scale);

	Matrix4 getMatrix() const;

   private:
	Vector3 m_translation;
	Vector3 m_rotation;
	Vector3 m_scale;
};
}  // namespace GLRT
