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

#include <bitset>
#include "character.h"

#define STATUS_RUNNING_LEFT 0
#define STATUS_RUNNING_RIGHT 1
#define STATUS_JUMPING 2
#define STATUS_OFFGROUND 3

typedef unsigned int uint;

class Player: public Character {
private:
	std::bitset<4> status;

public:
	Player();

	void status_set(uint _direction);
	void status_unset(uint _direction);
	void apply_user_forces();
	const std::bitset<4> & bitwise_status() const;
};

#endif // _PLAYER_H