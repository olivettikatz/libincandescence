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

/*! \file FontList.h
 *  \brief Contains utilities for listing all fonts on the system.
 *  Uses Fontconfig. */

#ifndef __LIB_INCANDESCENCE_FONTLIST_H
#define __LIB_INCANDESCENCE_FONTLIST_H

#include "../util/util.h"
#include <fontconfig/fontconfig.h>

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Initially false, set to true when Fontconfig library has been initialized. Ensures that Fontconfig-specific calls are
	 *  not made before it is initialized and ensures that Fontconfig is only initialized once. */
	extern bool fontConfigHasBeenInitialized;

	/*! Initially false, set to true if Fontconfig library has been uninitialized before. Ensures that if it is re-loaded,
	 *  that it is done properly. */
	extern bool fontConfigHasBeenDestroyed;

	/*! Fontconfig specific variable. */
	extern FcPattern *fontConfigPattern;

	/*! Fontconfig specific variable. */
	extern FcFontSet *fontConfigFontSet;

	/*! Fontconfig specific variable. */
	extern FcObjectSet *fontConfigObjectSet;

	/*! Fontconfig specific variable. */
	extern FcConfig *fontConfigConfig;

	/*! Helper method for Fontconfig. */
	void configureFontConfig();

	/*! Helper method for Fontconfig. */
	void unconfigureFontConfig();

	/*! Helper method for populating Fontconfig's font list. */
	map<string, string> populateHelper();

	/*! Class for listing all fonts in system. */
	class FontList
	{
	protected:
		map<string, string> content;

	public:
		/*! Constructure. */
		FontList() {}

		/*! Searches for all fonts on system.
		 *  \warning If running this for the first time on a system, it may take a few minutes to create Fontconfig cache. */
		void populate();

		/*! Returns vector of names of all of the fonts on the system. */
		vector<string> names();

		/*! Returns vector of paths of all of the font files for all fonts on the system. */
		vector<string> paths();

		/*! Returns the path of the font file associated with a font of a certain name. */
		string getPath(string name);
	};
}

#endif