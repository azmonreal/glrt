#pragma once

#include "camera.hpp"
#include "light.hpp"
#include "model.hpp"

namespace GLRT {
void glrtDrawMesh(Mesh& mesh, Matrix4 model_matrix, Material material, Light ambient, std::vector<Light> lights, bool debug=false);
void glrtDrawModel(Model& model, Light ambient, std::vector<Light> lights, bool debug=false);
void glrtUpdateModel(Model& model, double delta_time);

void glrtDrawLights(std::vector<Light> lights);

void glrtDrawLine(Vector3 start, Vector3 end, Color start_color, Color end_color);
void glrtDrawLine(Vector3 start, Vector3 end, Color c={1});
void glrtDrawSphere(Vector3 pos, double radius, Color c={1});

void glrtUpdateCamera(Camera camera);

}  // namespace GLRT
