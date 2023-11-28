#include "keyframe.hpp"

namespace GLRT {
Keyframe::Keyframe() : transform(), time(0.0) {}
Keyframe::Keyframe(const Transform& transform, double time, InterpolationMode interpolationMode, Transform cp1, Transform cp2) : transform(transform), time(time), interpolationMode(interpolationMode) {
	controlPoints[0] = cp1;
	controlPoints[1] = cp2;
}

Keyframe::~Keyframe() {}
}  // namespace GLRT
