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

 /* \file SoundExtern.h
  * \brief Contains class for playing sounds using external tools.
  * \warning Currently only supports Mac OS X. */

#ifndef __LIB_INCANDESCENCE_AUDIO_EXTERN_H
#define __LIB_INCANDESCENCE_AUDIO_EXTERN_H

#include "Sound.h"
#include <unistd.h>

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Implementation of Sound using external tools to play sounds. */
	class SoundExtern : public Sound
	{
	protected:
		char *argv[9];

	public:
		/*! Simple constructor (see Sound.h). */
		SoundExtern(string p = "", double v = 1.0) : Sound(p, v) {}

		/*! Loads sound. */
		void load();

		/*! Plays sound. */
		void play();
	};
}

#endif