#include "material.hpp"

namespace GLRT {
Material::Material() : ambient{{1.0, 1.0, 1.0}}, diffuse{{0.5, 0.5, 0.5}}, specular{{0.5, 0.5, 0.5}} {}
Material::~Material() {}
}  // namespace GLRT
