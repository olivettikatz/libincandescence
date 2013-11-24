#include "Sound.h"

namespace incandescence
{
	bool Sound::empty()
	{
		return path.empty();
	}

	bool Sound::valid()
	{
		if (empty())
			return false;

		if (fileExists(path) == false)
			return false;

		return true;
	}

	void Sound::load()
	{
	}

	void Sound::play()
	{
	}
}