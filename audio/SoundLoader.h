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

/*! \file SoundLoader.h
 *  \brief Class for loading and organizing many sounds of any subclass of Sound (see Sound.h). 
 *  \warning If you use SoundLoader<Sound>, no sound will play - you must use a subclass of Sound (see Sound.h). 
 */

#ifndef __LIB_INCANDESCENCE_AUDIO_H
#define __LIB_INCANDESCENCE_AUDIO_H

#include "../util/util.h"

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Class for loading and organizing many sounds. For example: 
	* \include TestSoundExtern.h */
	template<typename T> class SoundLoader
	{
	protected:
		map<string, T> content;

	public:
		/*! Constructor. */
		SoundLoader() {}

		/*! Adds a sound.
		 *  \param n Name of the sound.
		 *  \param s Sound subclass object. */
		void add(string n, T s);

		/*! Adds a sound.
		 *  \param n Name of the sound.
		 *  \param p Path of the sound file.
		 *  \param v Volume to play the sound at. (see Sound.h) */
		void add(string n, string p, double v = 1.0);

		/*! Sounds are not loaded upon adding. They have to be all loaded simultaneously with this method. */
		void loadAll();

		/*! Plays a sound with this particular name. */
		void play(string n);
	};

	template<typename T> void SoundLoader<T>::add(string n, T s)
	{
		content[n] = s;
	}

	template<typename T> void SoundLoader<T>::add(string n, string p, double v)
	{
		content[n] = T(p, v);
	}

	template<typename T> void SoundLoader<T>::loadAll()
	{
		for (typename map<string, T>::iterator i = content.begin(); i != content.end(); i++)
		{
			i->second.load();
		}
	}

	template<typename T> void SoundLoader<T>::play(string n)
	{
		if (content.find(n) != content.end())
			content[n].play();
	}
}

#endif