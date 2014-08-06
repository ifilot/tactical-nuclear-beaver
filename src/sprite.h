/**************************************************************************
 *   sprite.h                                                             *
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

#ifndef _SPRITE_H
#define _SPRITE_H

#define GRAVITY_CONSTANT 0.3f
#define TIME_CONSTANT 1.0f

#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <string>
#include <stdio.h>
#include <iostream>

class Sprite{
protected:
	float pos_x;
	float pos_y;

	int img_width;
	int img_height;

	float vx;
	float vy;

	float fx;
	float fy;

	bool moveable;
	bool apply_gravity;
	bool visible;
	GLuint texture;

public:
	// constructors and initialisers
	Sprite();
	void init();

	// setters
	void set_position(float _x, float _y);
	void scale(const float &ratio);

	// getters
	const GLuint & get_texture();
	const float & get_x();
	const float & get_y();
	const int & get_width();
	const int & get_height();

	// other methods
	void update();

protected:
	GLuint LoadTexture(const char* filename);
};

#endif // _SPRITE_H