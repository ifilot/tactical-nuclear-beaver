/**************************************************************************
 *   physics_engine.cxx                                                   *
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

#include "physics_engine.h"

PhysicsEngine::PhysicsEngine() {

}

void PhysicsEngine::reset_forces() {
	for(unsigned int i=0; i<this->sprites.size(); i++) {
		if(this->sprites[i]->is_moveable()) {
			this->sprites[i]->reset_forces();
		}
	}
}

void PhysicsEngine::set_sprites(std::vector<Sprite*> _sprites) {
	this->sprites = _sprites;
}

void PhysicsEngine::update_sprites() {
	this->reset_forces();
	this->apply_gravity();
	dynamic_cast<Player*>(this->sprites[0])->apply_user_forces();
	this->apply_friction();
	for(unsigned int i=0; i<this->sprites.size(); i++) {
		this->sprites[i]->update();
	}
	this->collission_detect();
}

void PhysicsEngine::collission_detect() {
	// only perform this action for the player (no NPC installed yet)
	uint i = 0;
	bool collission = false;
	for(unsigned int j=i+1; j<this->sprites.size(); j++) {
		float dx = this->calculate_dx(this->sprites[i], this->sprites[j]);
		float dy = this->calculate_dy(this->sprites[i], this->sprites[j]);

		if(dx < 0 && dy < 0) {
			this->sprites[i]->set_position(this->sprites[i]->get_x(), this->sprites[i]->get_y() - dy - 2);
			collission = true;
		}
	}
	if(collission) {
		dynamic_cast<Player*>(this->sprites[i])->status_unset(STATUS_OFFGROUND);
	} else {
		dynamic_cast<Player*>(this->sprites[i])->status_set(STATUS_OFFGROUND);
	}
}

void PhysicsEngine::apply_gravity() {
	for(unsigned int i=0; i<this->sprites.size(); i++) {
		if(this->sprites[i]->is_moveable()) {
			this->sprites[i]->add_force_x(-FRICTION_CONSTANT * this->sprites[i]->get_vx());
			this->sprites[i]->add_force_y(-FRICTION_CONSTANT * this->sprites[i]->get_vy());
		}
	}
}

void PhysicsEngine::apply_friction() {
	for(unsigned int i=0; i<this->sprites.size(); i++) {
		if(this->sprites[i]->is_pulled_by_gravity()) {
			this->sprites[i]->add_force_y(-GRAVITY_CONSTANT);
		}
	}
}

float PhysicsEngine::calculate_dx(Sprite* a, Sprite* b) {
	float half_extents_a_x = a->get_width() / 2.0f;
	float half_extents_b_x = b->get_width() / 2.0f;

	float centre_a_x = (a->get_x()) + half_extents_a_x;
	float centre_b_x = (b->get_x()) + half_extents_b_x;

	float d_x = abs(centre_b_x - centre_a_x) - (half_extents_a_x + half_extents_b_x);

	return d_x;
}

float PhysicsEngine::calculate_dy(Sprite* a, Sprite* b) {
	float half_extents_a_y = a->get_height() / 2.0f;
	float half_extents_b_y = b->get_height() / 2.0f;

	float centre_a_y = (a->get_y()) + half_extents_a_y;
	float centre_b_y = (b->get_y()) + half_extents_b_y;

	float d_y = abs(centre_b_y - centre_a_y) - (half_extents_a_y + half_extents_b_y);

	return d_y;
}

float PhysicsEngine::calculate_dx_next_timestep(Sprite* a, Sprite* b) {
	float half_extents_a_x = a->get_width() / 2.0f;
	float half_extents_b_x = b->get_width() / 2.0f;

	float centre_a_x = (a->get_x() + a->get_vx() * TIME_CONSTANT) + half_extents_a_x;
	float centre_b_x = (b->get_x() + b->get_vx() * TIME_CONSTANT) + half_extents_b_x;

	float d_x = abs(centre_b_x - centre_a_x) - (half_extents_a_x + half_extents_b_x);

	return d_x;
}

float PhysicsEngine::calculate_dy_next_timestep(Sprite* a, Sprite* b) {
	float half_extents_a_y = a->get_height() / 2.0f;
	float half_extents_b_y = b->get_height() / 2.0f;

	float centre_a_y = (a->get_y() + a->get_vy() * TIME_CONSTANT) + half_extents_a_y;
	float centre_b_y = (b->get_y() + b->get_vy() * TIME_CONSTANT) + half_extents_b_y;

	float d_y = abs(centre_b_y - centre_a_y) - (half_extents_a_y + half_extents_b_y);

	return d_y;
}

bool PhysicsEngine::does_collide(Sprite* a, Sprite* b) {
	return (this->calculate_dx(a, b) < 0.0f) && 
			(this->calculate_dy(a, b) < 0.0f);
}