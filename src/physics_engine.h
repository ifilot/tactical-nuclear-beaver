/**************************************************************************
 *   physics_engine.h                                                     *
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

#ifndef _PHYSICS_ENGINE_H
#define _PHYSICS_ENGINE_H

#include <vector>
#include <stdlib.h>

#include "physics_constants.h"
#include "sprite.h"
#include "player.h"

class PhysicsEngine{
private:
	std::vector<Sprite*> sprites;

public:
	PhysicsEngine();
	void reset_forces();
	void apply_gravity();
	void apply_friction();
	void set_sprites(std::vector<Sprite*> _sprites);
	void update_sprites();

private:
	void collission_detect();
	bool does_collide(Sprite* a, Sprite* b);
	float calculate_dx(Sprite* a, Sprite* b);
	float calculate_dy(Sprite* a, Sprite* b);
	float calculate_dx_next_timestep(Sprite* a, Sprite* b);
	float calculate_dy_next_timestep(Sprite* a, Sprite* b);
};

#endif // _PHYSICS_ENGINE_H