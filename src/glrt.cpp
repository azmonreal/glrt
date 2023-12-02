#include "glrt.hpp"

#include <GL/freeglut_std.h>
#include <GL/gl.h>

#include <iostream>

#include "camera.hpp"
#include "light.hpp"

namespace GLRT {

void glrtDrawMesh(Mesh& mesh, Matrix4 model_matrix, Material material, Light ambient, std::vector<Light> lights, bool debug) {
	Transform mesh_transform = mesh.transform;
	auto combined_matrix = model_matrix * mesh_transform.getMatrix() * mesh.animation.GetTransform().getMatrix();

	for(auto face : mesh.faces) {
		Vector3 normal = Vector4{combined_matrix * Matrix4x1{face.normal, 0}}.normalized();
		Vector3 center = Vector4{combined_matrix * Matrix4x1{face.center, 1}};

		if(debug) {
			glrtDrawLine(center, center + normal, {1}, {1});
		}

		Color ambient_c = material.ambient * ambient.color * ambient.intensity;

		Color diffuse_c;

		for(auto light : lights) {
			auto light_c = light.color;
			auto light_i = light.intensity;
			auto light_dir = light.direction.normalized();
			auto light_pos = light.position;

			Vector3 dir_to_light = (light_pos - Vector3{center}).normalized();

			auto temp = light_dir.length();
			if(light_dir.length() != 0) dir_to_light = light_dir * -1;

			double factor = normal.dot(dir_to_light);
			if(factor < 0) factor = 0;

			diffuse_c += light_c * light_i * factor * material.diffuse;

			if(debug) {
				glrtDrawLine(center, center + dir_to_light * factor, light_c * light_i, light_c);
			}
		}

		Color face_c = ambient_c + diffuse_c;

		glColor3dv(face_c.data());

		switch(face.indices.size()) {
			case 3:
				glBegin(GL_TRIANGLES);
				break;
			case 4:
				glBegin(GL_QUADS);
				break;
			default:
				glBegin(GL_POLYGON);
				break;
		}

		for(auto index : face.indices) {
			auto transformed_vertex = combined_matrix * Matrix4x1{mesh.vertices[index].position, 1};
			glVertex3dv(Vector4{transformed_vertex}.data());
		}

		glEnd();
	}
}

void glrtDrawModel(Model& model, Light ambient, std::vector<Light> lights, bool debug) {
	auto model_matrix = model.transform.getMatrix() * model.animation.GetTransform().getMatrix();

	for(auto& mesh : model.meshes) {
		auto material = model.materials[mesh.second.material];

		glrtDrawMesh(mesh.second, model_matrix, model.materials[mesh.second.material], ambient, lights, debug);
	}
}

void glrtUpdateModel(Model& model, double time_delta) {
	model.animation.Update(time_delta);
	for(auto& mesh : model.meshes) {
		mesh.second.animation.Update(time_delta);
	}
}

void glrtDrawLights(std::vector<Light> lights) {
	for(auto light : lights) {
		glrtDrawSphere(light.position, 0.1, light.color);

		if(light.direction.length() > 0) {
			glrtDrawLine(light.position, light.position + light.direction, light.color, light.color);
		}
	}
}

void glrtDrawLine(Vector3 start, Vector3 end, Color start_color, Color end_color) {
	glBegin(GL_LINES);
	glColor3dv(start_color.data());
	glVertex3dv(start.data());
	glColor3dv(end_color.data());
	glVertex3dv(end.data());
	glEnd();
}

void glrtDrawLine(Vector3 start, Vector3 end, Color c) {
	glrtDrawLine(start, end, c, c);
}

void glrtDrawSphere(Vector3 pos, double radius, Color c) {
	glColor3dv(c.data());
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glutSolidSphere(radius, 20, 20);
	glPopMatrix();
}

void glrtUpdateCamera(Camera camera) {
	auto position = camera.GetPosition();
	auto forward = camera.GetForward();
	auto up = camera.GetUp();

	auto dir = (position + forward);

	gluLookAt(
		position[0], position[1], position[2],
		dir[0], dir[1], dir[2],
		up[0], up[1], up[2]);
}
}  // namespace GLRT
