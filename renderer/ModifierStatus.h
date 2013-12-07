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

/*! \file ModifierStatus.h
 *  \brief Class describing current keyboard modifier status. */

/*! \def INCD_MOD_SIZE
 *  \brief Number of modifiers. */

#ifndef __LIB_INCANDESCENCE_MODIFIER_H
#define __LIB_INCANDESCENCE_MODIFIER_H

#include "../util/Util.h"
#include <GLFW/glfw3.h>

#define INCD_MOD_SIZE 4

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! \brief Class describing current keyboard modifier status. */
	class ModifierStatus
	{
	public:
		/*! Enumerator of different modifiers, values are actually indexes for status array. */
		typedef enum
		{
			Shift,
			Control,
			Alt,
			Mod
		} Modifier;

		/*! Side of the modifier (for telling the difference between LMod and RMod). */
		typedef enum
		{
			Left,
			Right,
			Either
		} Side;

		/*! Status of all modifiers. */
		bool status[INCD_MOD_SIZE];

		/*! Constructor. */
		ModifierStatus() {clear();}

		/*! Constructor from OpenGL modifier flags. */
		ModifierStatus(int flags);

		/*! Sets current status to that of another ModifierStatus. */
		void setTo(ModifierStatus &m);

		/*! Resets status. */
		void clear();

		/*! Gets status of shift. */
		bool &shift();

		/*! Gets status of control. */
		bool &control();

		/*! Gets status of alt. */
		bool &alt();

		/*! Gets status of mod. */
		bool &mod();

		/*! Creates displayable string describing modifier status. */
		string toString();
	};
}

#endif