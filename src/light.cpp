#include "light.hpp"

namespace GLRT {
Light::Light() {}
Light::Light(Vector3 color, Vector3 position, Vector3 direction, double intensity) : color(color), position(position), direction(direction), intensity(intensity) {}
Light::~Light() {}
}  // namespace GLRT
