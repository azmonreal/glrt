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

Model cube{};
Light ambient;
std::vector<Light> lights;

float grados = 0;
void display(void) {
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto light : lights){
		// draw sphere
		glColor3dv(light.color.data());
		glPushMatrix();
		glTranslated(light.position[0], light.position[1], light.position[2]);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();

		if(light.direction.length() > 0){
			glBegin(GL_LINES);
			glVertex3dv(light.position.data());
			glVertex3dv((light.position + light.direction.normalized()).data());
			glEnd();
		}
	}

	int color_index = 0;

	auto model_transform = cube.transform.getMatrix();
	for(auto& mesh : cube.meshes) {
		auto mesh_transform = mesh.transform.getMatrix();
		auto combined_transformed = model_transform * mesh_transform;

		Vector3 mesh_color = Vector3{{0.5, 0.5, 0.5}};

		auto ambient_color = ambient.color * mesh_color;

		for(auto& face : mesh.faces) {

			auto center = Vector4{combined_transformed * Matrix4x1{face.center, 1}};
			auto normal = Vector4{combined_transformed * Matrix4x1{face.normal, 0}};

			glColor3dv(Vector3{{1.0, 1.0, 1.0}}.data());

			// glBegin(GL_LINES);
			// glVertex3dv(center.data());
			// glVertex3dv((center + normal * 0.2).data());
			// glEnd();

			Vector3 diffuse_color{};

			for(auto light : lights){
				auto light_color = light.color;
				auto light_direction = light.direction.normalized();
				auto light_position = light.position;

				Vector3 dir_to_light;

				if(light_direction.length() > 0) dir_to_light = light_direction * -1;
				else dir_to_light = (light_position - Vector3{center}).normalized();

				glColor3dv(light_color.data());
				// glBegin(GL_LINES);
				// glVertex3dv(center.data());
				// glVertex3dv((center + dir_to_light *0.2).data());
				// glEnd();

				double factor = normal.dot(dir_to_light);

				if(factor < 0) factor = 0;

				diffuse_color += light_color * mesh_color * factor;
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

	gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
	std::string base_path = "/home/azmonreal/dev/libs/glrt";

	cube.load("/home/azmonreal/dev/libs/glrt/examples/resources/sphere.obj");
	// cube.print();

	cube.transform.scale({2});
	cube.transform.translate({{2, 0, -2}});
	// cube.transform.rotate({{10, 10, -10}});

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
	l3.color = {{0.0, 0.0, 1.0}};
	l3.position = {{0.0, 0.0, 0.0}};
	l3.direction = {{-1.0,1.0, -1.0}};
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
