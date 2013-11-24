#include "fontlist.h"

namespace incandescence
{
	bool fontConfigHasBeenInitialized;
	bool fontConfigHasBeenDestroyed;
	FcPattern *fontConfigPattern;
	FcFontSet *fontConfigFontSet;
	FcObjectSet *fontConfigObjectSet;
	FcConfig *fontConfigConfig;

	void configureFontConfig()
	{
		if (fontConfigHasBeenInitialized)
			return ;
		fontConfigHasBeenInitialized = true;

		if (!FcInit())
		{
			INCD_ERROR("could not initialize fontconfig.");
			return ;
		}

		fontConfigConfig = FcConfigGetCurrent();
		FcConfigSetRescanInterval(fontConfigConfig, 0);
		fontConfigPattern = FcPatternCreate();
		fontConfigObjectSet = FcObjectSetBuild(FC_FAMILY, FC_FILE, (char *)0);
		fontConfigFontSet = FcFontList(fontConfigConfig, fontConfigPattern, fontConfigObjectSet);
	}

	void unconfigureFontConfig()
	{
		if (fontConfigHasBeenDestroyed)
			return ;
		fontConfigHasBeenDestroyed = true;
		if (fontConfigFontSet != NULL)
			FcFontSetDestroy(fontConfigFontSet);
	}

	map<string, string> populateHelper()
	{
		map<string, string> rtn;
		for (int i = 0; fontConfigFontSet != NULL && i < fontConfigFontSet->nfont; i++)
		{
			FcPattern *font = fontConfigFontSet->fonts[i];
			string s = string((char *)FcNameUnparse(font));
			rtn[s.substr(0, s.find(":"))] = s.substr(s.find("=")+1);
		}
		return rtn;
	}

	void FontList::populate()
	{
		configureFontConfig();
		content = populateHelper();
	}

	vector<string> FontList::names()
	{
		vector<string> rtn;
		for (map<string, string>::iterator i = content.begin(); i != content.end(); i++)
			rtn.push_back(i->first);
		return rtn;
	}

	vector<string> FontList::paths()
	{
		vector<string> rtn;
		for (map<string, string>::iterator i = content.begin(); i != content.end(); i++)
			rtn.push_back(i->second);
		return rtn;
	}

	string FontList::getPath(string name)
	{
		return content[name];
	}
}