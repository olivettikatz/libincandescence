/* Copyright 2013 Oliver Katz
 *
 * This file is part of LibIncandescence.
 *
 * LibIncandescence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibIncandescene is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibIncandescence.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file Key.h
 *  \brief Class containing the data resulting from a keypress. */

#ifndef __LIB_INCANDESCENCE_KEY_H
#define __LIB_INCANDESCENCE_KEY_H

#include "../util/Util.h"
#include "ModifierStatus.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! \brief Class containing the data resulting from a keypress. */
	class Key
	{
	public:
		/*! Key values. */
		typedef enum
		{
			Null,
			Space, Escape, Enter, Tab, Backspace, Insert, Delete,
			Apostrophe, Comma, Period, Accent,
			Minus, Equal,
			Slash, Backslash,
			Semicolon,
			BracketLeft, BracketRight,
			Up, Down, Left, Right,
			PageUp, PageDown, Home, End,
			CapsLock, ScrollLock, NumLock, Print, Pause,
			Decimal, Divide, Multiply, Subtract, Add, KEnter,
			ShiftLeft, ShiftRight, ControlLeft, ControlRight, AltLeft, AltRight, ModLeft, ModRight, Menu,
			N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
			K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25
		} Symbol;

		/*! The key pressed. */
		Symbol value;

		/*! Whether the key should be shifted. 
		 *  \warning You can use shift in ModifierStatus (see ModifierStatus.h), but this supports capslock. */
		bool shift;

	protected:
		Symbol intToSymbol(int k);

	public:
		/*! Constructor. */
		Key() : value(Null) {}

		/*! Constructor.
		 *  \param k OpenGL key code
		 *  \param s Whether shift/capslock is on. */
		Key(int k, bool s = false) : value(intToSymbol(k)), shift(s) {}

		/*! Whether key is ASCII. */
		bool isASCII();

		/*! Converts key to ASCII if possible, otherwise returns 0. */
		char toASCII();
		
		/*! Converts key to string describing key value. */
		string toString();
	};
}

#endif