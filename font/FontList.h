#ifndef __LIB_INCANDESCENCE_FONTLIST_H
#define __LIB_INCANDESCENCE_FONTLIST_H

#include "../util/util.h"
#include <fontconfig/fontconfig.h>

namespace incandescence
{
	using namespace std;

	extern bool fontConfigHasBeenInitialized;
	extern bool fontConfigHasBeenDestroyed;
	extern FcPattern *fontConfigPattern;
	extern FcFontSet *fontConfigFontSet;
	extern FcObjectSet *fontConfigObjectSet;
	extern FcConfig *fontConfigConfig;

	void configureFontConfig();
	void unconfigureFontConfig();
	map<string, string> populateHelper();

	class FontList
	{
	protected:
		map<string, string> content;

	public:
		FontList() {}
		void populate();
		vector<string> names();
		vector<string> paths();
		string getPath(string name);
	};
}

#endif