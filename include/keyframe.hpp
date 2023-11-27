#pragma once

#include <vector>

#include "transform.hpp"

namespace GLRT {
class Keyframe {
   public:
	Keyframe();
	Keyframe(const Transform& transform, double time);
	~Keyframe();

	Transform transform;
	double time;
};

}  // namespace GLRT
