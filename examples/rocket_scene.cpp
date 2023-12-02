#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "camera.hpp"
#include "glrt.hpp"

using namespace GLRT;
using namespace std;

bool is_paused;

std::vector<Model> models{};
Light ambient{{1}, {{0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}}, 0.1};
std::vector<Light> lights;

Camera main_camera{Transform{
	{{20, 30, 60}},
	{{20, 186, 0}},
	{1},
}};

std::map<std::string, Color> colors = {
	{"red", {{1.0, 0.0, 0.0}}},
	{"green", {{0.0, 1.0, 0.0}}},
	{"blue", {{0.0, 0.0, 1.0}}},
	{"yellow", {{1.0, 1.0, 0.0}}},
	{"cyan", {{0.0, 1.0, 1.0}}},
	{"magenta", {{1.0, 0.0, 1.0}}},
	{"white", {{1.0, 1.0, 1.0}}},
	{"black", {{0.0, 0.0, 0.0}}},
};

void display(void) {
	static double last_frame_time;
	double current_time = glutGet(GLUT_ELAPSED_TIME);
	double time_delta = current_time - last_frame_time;
	last_frame_time = current_time;

	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glrtDrawLights(lights);

	for(auto& model : models) {
		if(!is_paused) {
			glrtUpdateModel(model, time_delta * 0.001);
		}
		glrtDrawModel(model, ambient, lights, false);
	}

	glutSwapBuffers();
	glFlush();
}

void init(void) {
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.1, 0.5, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	// gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glrtUpdateCamera(main_camera);

	glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			is_paused = !is_paused;
			break;
	}
}

void mouse_wheel(int button, int dir, int x, int y) {
	if(is_paused) {
		for(auto& model : models) {
			glrtUpdateModel(model, dir * 0.1);
		}
	}
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char* argv[]) {
	Light sun{{1}, {0}, {{-1.0, -1.0, -1.0}}, 0.8};
	lights.push_back(sun);

	Light grass_right{colors["green"], {{0.0, -1.0, 0.0}}, {{0, 1, 0}}, 0.3};
	lights.push_back(grass_right);

	lights.push_back({colors["yellow"], {}, {{0, -1, 0}}, 0.5});

	lights.push_back({colors["cyan"], {{-8, 15, 5}}, {0}, 0.7});
	lights.push_back({colors["magenta"], {{8, 15, -5}}, {0}, 0.7});

	Model grass;
	grass.load("resources/grass.obj");
	models.push_back(grass);

	Model launchpad;
	launchpad.load("resources/launchpad.obj");

	launchpad.animation = Animation{
		10,
		{
			Keyframe{
				{{{0, 0, 0}}, {{0, 0, 0}}, {1}},
				0,
				Keyframe::InterpolationMode::LINEAR,
			},
			Keyframe{
				{{{0, 0, 0}}, {{0, 360, 0}}, {1}},
				3,
				Keyframe::InterpolationMode::BEZIER,
				{{}, {{0, 450, 0}}, {1}},
				{{}, {{0, 530, 0}}, {1}},
			},
			Keyframe{
				{{{0, 0, 0}}, {{0, 600, 0}}, {1}},
				5,
			},
			Keyframe{
				{{{0, 0, 0}}, {{0, 700, 0}}, {1}},
				10,
			},

		},
	};
	models.push_back(launchpad);

	Model rocket;
	rocket.load("resources/rocket.obj");

	rocket.transform.translate({{0, 5, 0}});

	rocket.animation = Animation{
		10,
		{
			Keyframe{
				{{{0, 0, 0}}, {{0, -360, 0}}, {1}},
				0,
				Keyframe::InterpolationMode::LINEAR,
			},
			Keyframe{
				{{{0, 0, 0}}, {{0, 0, 0}}, {1}},
				3,
				Keyframe::InterpolationMode::BEZIER,
				{{{0, 3, 0}}, {{0, 0, 0}}, {1}},
				{{{7, 20, -2}}, {{-70, 0, 0}}, {1}},
			},
			Keyframe{
				{{{10, 20, -5}}, {{-80, 0, 0}}, {1}},
				5,
				Keyframe::InterpolationMode::BEZIER,
				{{{30, 40, -100}}, {{0, 0, 0}}, {1}},
				{{{80, 50, -200}}, {{0, 0, 0}}, {1}},
			},
			Keyframe{
				{{{80, 60, -200}}, {{0, 0, 0}}, {1}},
				8,
				Keyframe::InterpolationMode::BEZIER,
				{{{10, 20, 0}}, {{0, 0, 0}}, {1}},
				{{{10, 20, 0}}, {{0, 0, 0}}, {1}},
			},
		},
	};
	models.push_back(rocket);

	Model lever;
	lever.load("resources/lever.obj");

	lever.transform.scale(2);
	lever.transform.translate({{0, 15, 30}});

	lever.meshes["Stick"].animation = Animation{
		10,
		{
			Keyframe{{{0}, {{0, 0, 0}}, {1}}, 2},
			Keyframe{{{0}, {{0, 0, -80}}, {1}}, 3},
			Keyframe{{{0}, {{0, 0, -80}}, {1}}, 10},
		},
	};

	models.push_back(lever);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	// glutPostRedisplay();
	glutIdleFunc(display);
	glutMouseWheelFunc(mouse_wheel);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0; /* ISO C requires main to return int. */
}
