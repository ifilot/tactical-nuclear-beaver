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
	this->vx = 1;
}

void Player::status_set(uint _direction) {
	this->status.set(_direction);
}

void Player::status_unset(uint _direction) {
	this->status.reset(_direction);
}

const std::bitset<4> & Player::bitwise_status() const {
	return status;
}

void Player::apply_user_forces() {
	if(this->status.test(STATUS_RUNNING_LEFT)) {
		this->add_force_x(-RUNNING_CONSTANT);
	}
	if(this->status.test(STATUS_RUNNING_RIGHT)) {
		this->add_force_x(RUNNING_CONSTANT);
	}
	if(this->status.test(STATUS_JUMPING) && !this->status.test(STATUS_OFFGROUND)) {
		this->add_force_y(JUMPING_CONSTANT);
	}
}