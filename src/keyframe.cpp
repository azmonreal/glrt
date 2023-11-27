#include "keyframe.hpp"

namespace GLRT {
Keyframe::Keyframe() : transform(), time(0.0) {}
Keyframe::Keyframe(const Transform& transform, double time) : transform(transform), time(time) {}
Keyframe::~Keyframe() {}
}  // namespace GLRT
