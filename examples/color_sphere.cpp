#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "camera.hpp"
#include "glrt.hpp"

using namespace GLRT;
using namespace std;

std::vector<Model> models{};
Light ambient{{1}, {{0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}}, 0.5};
std::vector<Light> lights;

Camera main_camera{Transform{
	{{10, 10, 10}},
	{{36, -135, 0}},
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
		glrtUpdateModel(model, time_delta);
		glrtDrawModel(model, ambient, lights, false);
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

	glrtUpdateCamera(main_camera);

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
	Model sphere;
	sphere.load("resources/sphere.obj");

	sphere.transform.scale(Vector3{2});

	Transform kf1c{};
	kf1c.rotate(Vector3{{0, 0, 0}});
	Transform kf2c{};
	kf2c.rotate(Vector3{{0, 360, 0}});

	Keyframe k1{kf1c, 0, Keyframe::InterpolationMode::LINEAR, Transform{}, Transform{}};
	Keyframe k2{kf2c, 5000, Keyframe::InterpolationMode::LINEAR, Transform{}, Transform{}};

	sphere.animation = Animation{5000, {k1, k2}};
	sphere.animation.loopMode = Animation::LoopMode::LOOP;

	models.push_back(sphere);

	auto red_light = Light{
		{colors["red"]},
		{{-5.0, -5.0, 5.0}},
		{0},
		1.0,
	};
	auto blue_light = Light{
		{colors["blue"]},
		{{5.0, -5.0, -5.0}},
		{0},
		1.0,
	};
	auto magenta_light = Light{
		{colors["magenta"]},
		{{5.0, -5.0, 5.0}},
		{0},
		1.0,
	};
	auto green_light = Light{
		{colors["green"]},
		{{-5.0, 5.0, -5.0}},
		{0},
		1.0,
	};
	auto yellow_light = Light{
		{colors["yellow"]},
		{{-5.0, 5.0, 5.0}},
		{0},
		1.0,
	};
	auto cyan_light = Light{
		{colors["cyan"]},
		{{5.0, 5.0, -5.0}},
		{0},
		1.0,
	};
	auto white_light = Light{
		{colors["white"]},
		{{5.0, 5.0, 5.0}},
		{0},
		1.0,
	};

	lights.push_back(red_light);
	lights.push_back(blue_light);
	lights.push_back(magenta_light);
	lights.push_back(green_light);
	lights.push_back(yellow_light);
	lights.push_back(cyan_light);
	lights.push_back(white_light);

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
