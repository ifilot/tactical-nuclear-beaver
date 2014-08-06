/**************************************************************************
 *   sprite.cxx                                                           *
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

#include "sprite.h"

Sprite::Sprite() {

}

void Sprite::init() {
	this->vx = 0;
	this->vy = 0;
	this->fx = 0;
	this->fy = 0;
	this->visible = true;
}

void Sprite::set_position(float _x, float _y) {
	this->pos_x = _x;
	this->pos_y = _y;
}

void Sprite::add_force(const float &fx, const float &fy) {
	this->add_force_x(fx);
	this->add_force_y(fy);
}

void Sprite::add_force_x(const float &_fx) {
	this->fx += _fx;
}

void Sprite::add_force_y(const float &_fy) {
	this->fy += _fy;
}

void Sprite::set_velocity(const float &vx, const float &vy) {
	this->set_velocity_x(vx);
	this->set_velocity_y(vy);
}

void Sprite::set_velocity_x(const float &_vx) {
	this->vx = _vx;
}

void Sprite::set_velocity_y(const float &_vy) {
	this->vy = _vy;
}

void Sprite::feels_gravity(bool _gravity) {
	this->apply_gravity = _gravity;
}


void Sprite::reset_forces() {
	this->fx = 0.0f;
	this->fy = 0.0f;
}

const GLuint & Sprite::get_texture() {
	return this->texture;
}

const float & Sprite::get_x() const {
	return this->pos_x;
}

const float & Sprite::get_y() const {
	return this->pos_y;
}

const float & Sprite::get_vx() const {
	return this->vx;
}

const float & Sprite::get_vy() const {
	return this->vy;
}

const int & Sprite::get_width() const {
	return this->img_width;
}

const int & Sprite::get_height() const {
	return this->img_height;
}

bool Sprite::is_moveable() const {
	return this->moveable;
}

bool Sprite::is_pulled_by_gravity() const {
	return this->apply_gravity;
}

void Sprite::scale(const float &ratio) {
	this->img_width *= ratio;
	this->img_height *= ratio;
}

GLuint Sprite::LoadTexture(const char* filename) {
	int channels = 0;

	unsigned char* image = SOIL_load_image(
		filename,
		&this->img_width, &this->img_height, &channels,
		SOIL_LOAD_AUTO
	);

	if(image == NULL) {
		// FIXME: ADD ERROR MESSAGE HERE
		return 0;
	}

	GLuint tex_2d =SOIL_create_OGL_texture(
		image,
		this->img_width, this->img_height, channels,
	 	SOIL_CREATE_NEW_ID,
	 	SOIL_FLAG_MIPMAPS | 
	 	SOIL_FLAG_INVERT_Y | 
	 	SOIL_FLAG_NTSC_SAFE_RGB | 
	 	SOIL_FLAG_COMPRESS_TO_DXT
	);

	SOIL_free_image_data(image);

	return tex_2d;
}

void Sprite::update() {
	if(moveable) {
		// apply forces to velocity
		this->vx += this->fx * TIME_CONSTANT;
		this->vy += this->fy * TIME_CONSTANT;

		// apply velocity to position
		this->pos_x += this->vx * TIME_CONSTANT;
		this->pos_y += this->vy * TIME_CONSTANT;
		//std::cout << "Updating sprite " << pos_x << std::endl;
	}
}