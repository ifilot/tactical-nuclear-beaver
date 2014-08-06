/**************************************************************************
 *   player.h                                                             *
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

#ifndef _PLAYER_H
#define _PLAYER_H

#include "character.h"

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1

class Player: public Character {
private:
	bool jumping;
	bool running;
	bool running_direction;

public:
	Player();

	void set_jumping(bool _jumping);
	void set_running(bool _jumping);
	void set_running_direction(bool _direction);
	void apply_user_forces();
};

#endif // _PLAYER_H