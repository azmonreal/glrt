#pragma once

#include "transform.hpp"
#include "types.hpp"
namespace GLRT {
class Camera {
   public:
	Camera();
	Camera(Transform transform);
	~Camera();

	Vector3 GetPosition() const;
	Vector3 GetForward() const;
	Vector3 GetUp() const;

	Transform transform;
};
}  // namespace GLRT
