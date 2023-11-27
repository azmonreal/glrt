#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "model.hpp"

using namespace GLRT;

Model cube{};

std::vector<Vector3> vertex_list = {
	{{-1.0, -1.0, -1.0}},
	{{1.0, -1.0, -1.0}},
	{{1.0, 1.0, -1.0}},
	{{-1.0, 1.0, -1.0}},
	{{-1.0, -1.0, 1.0}},
	{{1.0, -1.0, 1.0}},
	{{1.0, 1.0, 1.0}},
	{{-1.0, 1.0, 1.0}}};

std::vector<std::array<int, 3>> index_list = {
	{{0, 1, 2}},
	{{0, 2, 3}},
	{{4, 6, 5}},
	{{4, 7, 6}},
	{{4, 5, 1}},
	{{4, 1, 0}},
	{{3, 2, 6}},
	{{3, 6, 7}},
	{{1, 5, 6}},
	{{1, 6, 2}},
	{{4, 0, 3}},
	{{4, 3, 7}}};

float grados = 0;
void display(void) {
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	for(auto& mesh : cube.meshes) {
		for(auto& face : mesh.faces) {
			for(auto& index : face.indices) {
				auto& vertex = mesh.vertices[index];
				glVertex3dv(vertex.position.data());
			}
		}
	}
	glEnd();

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
	Mesh cube_mesh{};

	for(auto& vertex : vertex_list) {
		cube_mesh.vertices.push_back(vertex);
	}

	for(auto& index : index_list) {
		Face f;

		for(auto& i : index) {
			f.indices.push_back(i);
		}

		cube_mesh.faces.push_back(f);
	}

	cube.meshes.push_back(cube_mesh);

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
