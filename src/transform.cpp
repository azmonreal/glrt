#include "transform.hpp"

#include <cmath>
#include <iostream>

namespace GLRT {
Matrix4 Transform::translation_matrix(const Vector3& translation) {
	Matrix4 matrix = Matrix4::identity();
	matrix[0][3] = translation[0];
	matrix[1][3] = translation[1];
	matrix[2][3] = translation[2];
	return matrix;
}

Matrix4 Transform::rotation_matrix(const Vector3& axis, double angle) {
	angle = angle * M_PI / 180;
	double c = cos(angle);
	double s = sin(angle);
	double t = 1 - c;

	double x = axis[0];
	double y = axis[1];
	double z = axis[2];

	Matrix4 matrix = Matrix4::identity();
	matrix[0][0] = x * x * (1 - c) + c;
	matrix[0][1] = x * y * (1 - c) - z * s;
	matrix[0][2] = x * z * (1 - c) + y * s;

	matrix[1][0] = y * x * (1 - c) + z * s;
	matrix[1][1] = y * y * (1 - c) + c;
	matrix[1][2] = y * z * (1 - c) - x * s;

	matrix[2][0] = z * x * (1 - c) - y * s;
	matrix[2][1] = z * y * (1 - c) + x * s;
	matrix[2][2] = z * z * (1 - c) + c;

	return matrix;
}

Matrix4 Transform::scale_matrix(const Vector3& scale) {
	Matrix4 matrix = Matrix4::identity();
	matrix[0][0] = scale[0];
	matrix[1][1] = scale[1];
	matrix[2][2] = scale[2];
	return matrix;
}

Transform::Transform() {
	m_translation = Vector3{{0, 0, 0}};
	m_rotation = Vector3{{0, 0, 0}};
	m_scale = Vector3{{1, 1, 1}};
}
Transform::~Transform() {}

void Transform::translate(const Vector3& translation) {
	m_translation += translation;
}

void Transform::rotate(const Vector3& rotation) {
	m_rotation += rotation;
}

void Transform::scale(const Vector3& scale) {
	m_scale *= scale;
}

Matrix4 Transform::getMatrix() const {
	Matrix4 translation = translation_matrix(m_translation);
	Matrix4 rotation = rotation_matrix({{0, 0, 1}}, m_rotation[2]) * rotation_matrix({{0, 1, 0}}, m_rotation[1]) * rotation_matrix({{1, 0, 0}}, m_rotation[0]);
	Matrix4 scale = scale_matrix(m_scale);

	auto local = translation * rotation * scale;

	return translation * rotation * scale;
}

Transform Transform::Lerp(const Transform& other, double t) const {
	Transform result;

	result.m_translation = m_translation + (other.m_translation - m_translation) * t;
	result.m_rotation = m_rotation + (other.m_rotation - m_rotation) * t;
	result.m_scale = m_scale + (other.m_scale - m_scale) * t;

	return result;
}

Transform Transform::BezierInterpolation(const Transform& other, const Transform& c1, const Transform& c2, double t) const {
	Transform result;

	result.m_translation = m_translation * pow(1 - t, 3) + c1.m_translation * 3 * t * pow(1 - t, 2) + c2.m_translation * 3 * pow(t, 2) * (1 - t) + other.m_translation * pow(t, 3);
	result.m_rotation = m_rotation * pow(1 - t, 3) + c1.m_rotation * 3 * t * pow(1 - t, 2) + c2.m_rotation * 3 * pow(t, 2) * (1 - t) + other.m_rotation * pow(t, 3);
	result.m_scale = m_scale * pow(1 - t, 3) + c1.m_scale * 3 * t * pow(1 - t, 2) + c2.m_scale * 3 * pow(t, 2) * (1 - t) + other.m_scale * pow(t, 3);

	return result;
}
}  // namespace GLRT
