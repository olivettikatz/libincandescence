#include "util.h"

namespace incandescence
{
	bool fileExists(string path)
	{
		ifstream file(path.c_str());
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
}