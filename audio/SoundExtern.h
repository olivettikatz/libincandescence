#ifndef __LIB_INCANDESCENCE_AUDIO_EXTERN_H
#define __LIB_INCANDESCENCE_AUDIO_EXTERN_H

#include "Sound.h"
#include <unistd.h>

namespace incandescence
{
	using namespace std;

	class SoundExtern : public Sound
	{
	protected:
		char *argv[9];

	public:
		SoundExtern(string p = "", double v = 1.0) : Sound(p, v) {}
		void load();
		void play();
	};
}

#endif