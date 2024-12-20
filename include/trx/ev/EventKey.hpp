/*
	`transaction-x` allows users to manage their personal expenses.
	Copyright (C) 2024  Diego Vaccher

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

namespace trx::ev
{

enum EventKey : size_t
{
	/*
		Application Events
	*/
    APPLICATION_SHOULD_CLOSE = 0x0000000000000001,
	BOOTSTRAP_FRAMEWORK		 = 0x00000000000000F0,

	/*
		Window Events
	*/
	WINDOW_RESIZE_EVENT		 = 0x0000000000001000,

	/*
		Layer Events
	*/
	PUSH_LAYER_EVENT		 = 0x0000000000000003,
	POP_LAYER_EVENT		     = 0x0000000000000004,

	PUSH_LAYER_DEFERRED		 = 0x0000000000000005,
	POP_LAYER_DEFERRED		 = 0x0000000000000006,

	/*
		Special Request
	*/
	REQUEST_WINDOW_SIZE		 = 0xF000000000000001,
};

} // ns trx::ev