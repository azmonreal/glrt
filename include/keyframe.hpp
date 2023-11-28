#pragma once

#include <vector>

#include "transform.hpp"

namespace GLRT {
class Keyframe {
   public:
	enum class InterpolationMode {
		STEP,
		LINEAR,
		BEZIER,
	};

	Keyframe();
	Keyframe(const Transform& transform, double time, InterpolationMode interpolationMode = InterpolationMode::LINEAR, Transform cp1 = Transform{}, Transform cp2 = Transform{});
	~Keyframe();

	Transform transform;
	Transform controlPoints[2];
	double time;

	InterpolationMode interpolationMode;
};

}  // namespace GLRT
