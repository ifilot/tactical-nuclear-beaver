/**************************************************************************
 *   player.cxx                                                           *
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

#include "player.h"

Player::Player() {
	this->init(); // always load default values
	this->set_position(500,500);
	this->texture = this->LoadTexture("images/sprites/beaver.png");
	this->scale(.5);
	this->moveable = true;
	this->apply_gravity = true;
	this->jumping = false;
	this->vx = 1;
}

void Player::set_jumping(bool _jumping) {
	this->jumping = _jumping;
}

void Player::set_running(bool _running) {
	this->running = _running;
}

void Player::set_running_direction(bool _direction) {
	this->running_direction = _direction;
}

void Player::apply_user_forces() {
	if(this->running) {
		if(this->running_direction == DIRECTION_LEFT) {
			this->add_force_x(-RUNNING_CONSTANT);
		} else {
			this->add_force_x(RUNNING_CONSTANT);
		}
		this->running = false;
	}
	if(this->jumping) {
		this->add_force_y(JUMPING_CONSTANT);
		this->jumping = false;
	}
}