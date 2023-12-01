#include "camera.hpp"

namespace GLRT {
Camera::Camera() : transform() {}
Camera::Camera(Transform transform) : transform(transform) {}
Camera::~Camera() {}

Vector3 Camera::GetPosition() const {
	return transform.getTranslation();
}

Vector3 Camera::GetForward() const {
	return Vector4{transform.getMatrix() * Matrix4x1{{0, 0, 1, 0}}};
}

Vector3 Camera::GetUp() const {
	return Vector4{transform.getMatrix() * Matrix4x1{{0, 1, 0, 0}}};
}

}  // namespace GLRT
