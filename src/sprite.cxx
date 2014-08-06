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

void Sprite::set_position(int _x, int _y) {
	this->pos_x = _x;
	this->pos_y = _y;
}

const GLuint & Sprite::get_texture() {
	return this->texture;
}

const int & Sprite::get_x() {
	return this->pos_x;
}

const int & Sprite::get_y() {
	return this->pos_y;
}

const int & Sprite::get_width() {
	return this->img_width;
}

const int & Sprite::get_height() {
	return this->img_height;
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
	 	//SOIL_FLAG_INVERT_Y | 
	 	SOIL_FLAG_NTSC_SAFE_RGB | 
	 	SOIL_FLAG_COMPRESS_TO_DXT
	);

	SOIL_free_image_data(image);

	return tex_2d;
}