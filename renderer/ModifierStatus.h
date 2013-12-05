#ifndef __LIB_INCANDESCENCE_MODIFIER_H
#define __LIB_INCANDESCENCE_MODIFIER_H

#include "../util/Util.h"
#include <GLFW/glfw3.h>

#define INCD_MOD_SIZE

namespace incandescence
{
	using namespace std;

	class ModifierStatus
	{
	public:
		typedef enum
		{
			Shift,
			Control,
			Alt,
			Mod
		} Modifier;

		typedef enum
		{
			Left,
			Right,
			Either
		} Side;

		bool status[INCD_MOD_SIZE];

		ModifierStatus() {clear();}
		ModifierStatus(int flags);
		void setTo(ModifierStatus &m);
		void clear();
		bool &shift();
		bool &control();
		bool &alt();
		bool &mod();
		string toString();
	};
}

#endif