#include "util.h"

namespace incandescence
{
	bool fileExists(string path)
	{
		ifstream file(path.c_str(), ios::in);
		if (file.is_open())
		{
			file.close();
			return true;
		}
		else
		{
			return false;
		}
	}

	string loadFile(string path)
	{
		ifstream file(path.c_str(), ios::in);
		if (file.is_open())
		{
			string page((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
			return page;
		}
		else
		{
			INCD_ERROR("could not open file: " << path);
			return "";
		}
	}
}