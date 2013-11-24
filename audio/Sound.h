#ifndef __LIB_INCANDESCENCE_SOUND_H
#define __LIB_INCANDESCENCE_SOUND_H

#include "../util/util.h"

namespace incandescence
{
	using namespace std;

	class Sound
	{
	public:
		string path;
		double volume;

		Sound(string p = "", double v = 1.0) : path(p), volume(v) {}
		Sound(const Sound &s) : path(s.path), volume(s.volume) {}
		bool empty();
		bool valid();
		virtual void load();
		virtual void play();
	};
}

#endif