#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "matrix4x1.hpp"
#include "model.hpp"

using namespace GLRT;

Model cube{};

// rubiks cube
std::vector<Vector3> colors = {
	{{1.0, 0.0, 0.0}},  // red
	{{0.0, 1.0, 0.0}},  // green
	{{0.0, 0.0, 1.0}},  // blue
	{{1.0, 1.0, 1.0}},  // white
	{{1.0, 1.0, 0.0}},  // yellow
	{{1.0, 0.5, 0.0}},  // orange

};

float grados = 0;
void display(void) {
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int color_index = 0;

	auto model_transform = cube.transform.getMatrix();
	for(auto& mesh : cube.meshes) {
		auto mesh_transform = mesh.transform.getMatrix();
		// std::cout << "mult: "<< (model_transform * mesh_transform).to_string() << std::endl;

		for(auto& face : mesh.faces) {
			glColor3dv(colors[color_index++ % colors.size()].data());

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
				auto transformed_vertex = model_transform * mesh_transform * Matrix4x1{mesh.vertices[index].position, 1};
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

	cube.load("/home/azmonreal/dev/libs/glrt/examples/resources/untitled.obj");
	// cube.print();

	cube.transform.scale({{1.2, 1.2, 1.2}});
	cube.transform.translate({{2, 0, -2}});
	cube.transform.rotate({{10, 10, -10}});

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
