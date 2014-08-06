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

#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <string>
#include <stdio.h>

class Sprite{
protected:
	int pos_x;
	int pos_y;

	int img_width;
	int img_height;

	bool moveable;
	GLuint texture;

public:
	Sprite();
	void set_position(int _x, int _y);
	const GLuint & get_texture();
	const int & get_x();
	const int & get_y();
	const int & get_width();
	const int & get_height();

	void scale(const float &ratio);

protected:
	GLuint LoadTexture(const char* filename);
};

#endif // _SPRITE_H