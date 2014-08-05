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

class Window {
private:
	unsigned int width;
	unsigned int height;
	unsigned char* image;
	std::vector<GLuint> textures;

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
	void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture);
};  

#endif //_WINDOW_H