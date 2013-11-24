#ifndef __LIB_INCANDESCENCE_AUDIO_H
#define __LIB_INCANDESCENCE_AUDIO_H

#include "../util/util.h"

namespace incandescence
{
	using namespace std;

	template<typename T> class SoundLoader
	{
	protected:
		map<string, T> content;

	public:
		SoundLoader() {}
		void add(string n, T s);
		void add(string n, string p, double v = 1.0);
		void loadAll();
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