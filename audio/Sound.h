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

/*! \file Sound.h
 *  \brief Contains Base Sound class, for playing sounds.
 *  Most basic audio class for LibIncandescence. */

#ifndef __LIB_INCANDESCENCE_SOUND_H
#define __LIB_INCANDESCENCE_SOUND_H

#include "../util/util.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Base class for playing sounds. 
	 *  \warning If you just use Sound for playing sounds, nothing will happen because the actual implementation of Sound::load and Sound::play have to be implemented in system-specific subclasses. */
	class Sound
	{
	public:
		/*! Path of sound file. */
		string path;

		/*! Volume to play sound at (0.0-1.0 of original volume). */
		double volume;

		/*! Simple constructure.
		 *  \param p Path of sound file.
		 *  \param v Volume of sound. */
		Sound(string p = "", double v = 1.0) : path(p), volume(v) {}

		/*! Copy constructure. */
		Sound(const Sound &s) : path(s.path), volume(s.volume) {}

		/*! Returns true if sound is uninitialized. */
		bool empty();

		/*! Returns true if sound is valid (sound file path exists and volume is within acceptable range). */
		bool valid();

		/*! Overloadable load method (see SoundExtern.h for examples). */
		virtual void load();

		/*! Overloadable play method (see SoundExtern.h for examples). */
		virtual void play();
	};
}

#endif