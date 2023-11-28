#include "keyframe.hpp"

namespace GLRT {
Keyframe::Keyframe() : transform(), time(0.0) {}
Keyframe::Keyframe(const Transform& transform, double time, InterpolationMode interpolationMode) : transform(transform), time(time), interpolationMode(interpolationMode) {}
Keyframe::~Keyframe() {}
}  // namespace GLRT
