/**************************************************************************
 *   window.h                                                             *
 *                                                                        *
 *   Tactical Nuclear Beaver                                              *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation, version 2.                             *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    *
 *   General Public License for more details.                             *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA            *
 *   02110-1301, USA.                                                     *
 *                                                                        *
 **************************************************************************/

#ifndef _WINDOW_H
#define _WINDOW_H

#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>

#include "physics_engine.h"
#include "player.h"
#include "floor.h"

#define CONTROL_KEYBOARD 0
#define CONTROL_JOYSTICK 1

#define KEYDELAY_CHANGE_CONTROL 0
#define KEYDELAY_CHANGE_CONTROL_DELAY 0.5

class Window {
private:
	unsigned int width;
	unsigned int height;
	unsigned char* image;
	PhysicsEngine* physics_engine;
	std::vector<Sprite*> sprites;
	unsigned short control;
	std::vector<double> keydelays;

	// couple of variables to track the fps
	double t0_value;
	int fps_frame_count;
	double fps;
	double current_time;
	double time_interval;

public:
	Window();
	int create(int argc, char *argv[]);

private:
	void draw_canvas();
	void draw_scene();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void error_callback(int error, const char* description);
	void write_text(uint _x, uint _y, std::string str, float fontsize, float r=0, float g=0, float b=0);
	GLuint LoadTexture(std::string filename);
	void draw_sprites();
	void load_sprites();
	void write_statistics();
	void calculate_fps();
	void joystick_control(GLFWwindow* window);
	void keyboard_control(GLFWwindow* window);
};  

#endif //_WINDOW_H