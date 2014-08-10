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
#include <iostream>

#include "physics_constants.h"

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
	virtual ~Sprite(){};
	void init();

	// setters
	void set_position(float _x, float _y);
	void scale(const float &ratio);
	void add_force(const float &fx, const float &fy);
	void add_force_x(const float &_fx);
	void add_force_y(const float &_fy);
	void set_velocity(const float &vx, const float &vy);
	void set_velocity_x(const float &_vx);
	void set_velocity_y(const float &_vy);
	void reset_forces();
	void feels_gravity(bool _gravity);

	// getters
	const GLuint & get_texture();
	const float & get_x() const;
	const float & get_y() const;
	const float & get_vx() const;
	const float & get_vy() const;
	const float & get_fx() const;
	const float & get_fy() const;
	const int & get_width() const;
	const int & get_height() const;
	bool is_moveable() const;
	bool is_pulled_by_gravity() const;

	// other methods
	virtual void update();

protected:
	GLuint LoadTexture(const char* filename);
};

#endif // _SPRITE_H