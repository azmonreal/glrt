#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "light.hpp"
#include "matrix4x1.hpp"
#include "model.hpp"

using namespace GLRT;
using namespace std;

std::vector<Model> models{};
Light ambient;
std::vector<Light> lights;

void draw_lights() {
	for(auto light : lights) {
		// draw sphere
		glColor3dv(light.color.data());
		glPushMatrix();
		glTranslated(light.position[0], light.position[1], light.position[2]);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();

		if(light.direction.length() > 0) {
			glBegin(GL_LINES);
			glVertex3dv(light.position.data());
			glVertex3dv((light.position + light.direction.normalized()).data());
			glEnd();
		}
	}
}
void draw_model(Model& model) {
	model.animation.Update(0.01);

	auto model_transform = model.getTransform();

	for(auto& mesh : model.meshes) {
		auto material = model.materials[mesh.material];

		auto mesh_transform = mesh.transform.getMatrix();
		auto combined_transformed = model_transform * mesh_transform;

		Vector3 mesh_color = Vector3{{0.5, 0.5, 0.5}};

		auto ambient_color = ambient.color * material.ambient;

		for(auto& face : mesh.faces) {
			auto center = Vector4{combined_transformed * Matrix4x1{face.center, 1}};
			auto normal = Vector4{combined_transformed * Matrix4x1{face.normal, 0}}.normalized();

			glColor3dv(Vector3{{1.0, 1.0, 1.0}}.data());

			// glBegin(GL_LINES);
			// glVertex3dv(center.data());
			// glVertex3dv((center + normal * 0.2).data());
			// glEnd();

			Vector3 diffuse_color{};

			for(auto light : lights) {
				auto light_color = light.color;
				auto light_direction = light.direction.normalized();
				auto light_position = light.position;

				Vector3 dir_to_light;

				if(light_direction.length() > 0) dir_to_light = light_direction * -1;
				else
					dir_to_light = (light_position - Vector3{center}).normalized();

				glColor3dv(light_color.data());
				// glBegin(GL_LINES);
				// glVertex3dv(center.data());
				// glVertex3dv((center + dir_to_light *0.2).data());
				// glEnd();

				double factor = normal.dot(dir_to_light);

				if(factor < 0) factor = 0;

				diffuse_color += light_color * factor * material.diffuse;
			}

			auto face_color = ambient_color + diffuse_color;

			glColor3dv(face_color.data());

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

			for(auto& index : face.indices) {
				auto transformed_vertex = combined_transformed * Matrix4x1{mesh.vertices[index].position, 1};
				// std::cout << Vector4{transformed_vertex} << std::endl;
				glVertex3dv(Vector4{transformed_vertex}.data());
			}
			glEnd();
		}
	}
}

void display(void) {
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_lights();

	for(auto& model : models) {
		draw_model(model);
	}

	glutSwapBuffers();
	glFlush();
}

void init(void) {
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	// gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv) {
	Model sphere{};
	sphere.load("resources/sphere.obj");

	sphere.transform.scale({2});
	sphere.transform.translate({{2, 0, -2}});

	Transform kf1{};
	kf1.scale({1});
	Transform kf2{};
	kf2.scale({1.5});
	Transform kf3{};
	kf3.scale({2});
	sphere.animation = Animation{3, {{kf1, 0}, {kf2, 1}, {kf3, 2}}};
	sphere.animation.loopMode = Animation::LoopMode::PING_PONG;

	// models.push_back(sphere);

	Model cube;
	cube.load("resources/cube.obj");
	cube.transform.translate({{-2, 0, 0}});
	// cube.transform.rotate({{10, 10, -10}});
	//
	Transform kf1c{};
	kf1c.translate({{-3, 0, -3}});
	// kf1c.rotate(Vector3{{0, 0, 0}});
	Transform kf2c{};
	kf2c.translate({{3, 0, 3}});
	// kf2c.rotate(Vector3{{0, 30, 0}});
	Transform kf3c{};
	kf3c.translate({{-3, 0, 0}});
	// kf3c.rotate(Vector3{{0, 60, 0}});

	Transform c1{};
	c1.translate({{-3, 0, 0}});
	Transform c2{};
	c2.translate({{3, 0, 0}});

	Keyframe k1{kf1c, 0, Keyframe::InterpolationMode::BEZIER};
	Keyframe k2{kf2c, 10, Keyframe::InterpolationMode::BEZIER};

	k1.controlPoints[0] = c1;
	k1.controlPoints[1] = c2;

	k2.controlPoints[0] = c2;
	k2.controlPoints[1] = c1;

	cube.animation = Animation{10, {k1, k2}};
	cube.animation.loopMode = Animation::LoopMode::PING_PONG;
	// cube.animation.interpolationMode = Animation::InterpolationMode::STEP;
	models.push_back(cube);

	Model cubes;
	cubes.load("resources/cubes.obj");
	// models.push_back(cubes);

	ambient.color = {{0.5, 0.5, 0.5}};

	auto l1 = Light{};
	l1.color = {{1.0, 0.0, 0.3}};
	l1.position = {{0.0, 10.0, 0.0}};
	l1.direction = {{0.0, 0.0, 0.0}};
	lights.push_back(l1);

	auto l2 = Light{};
	l2.color = {{0.0, 1.0, 0.3}};
	l2.position = {{0.0, 10.0, 10.0}};
	l2.direction = {{0.0, 0.0, 0.0}};
	lights.push_back(l2);

	auto l3 = Light{};
	l3.color = {{0.7, 0.7, 0.7}};
	l3.position = {{0.0, 0.0, 0.0}};
	l3.direction = {{-1.0, -1.0, -1.0}};
	lights.push_back(l3);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	// glutPostRedisplay();
	glutIdleFunc(display);
	glutMainLoop();

	return 0; /* ISO C requires main to return int. */
}
