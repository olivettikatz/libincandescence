#include "ModifierStatus.h"

namespace incandescence
{
	ModifierStatus::ModifierStatus(int flags)
	{
		clear();
		if (flags & GLFW_MOD_SHIFT)
			status[Shift] = true;
		if (flags & GLFW_MOD_CONTROL)
			status[Control] = true;
		if (flags & GLFW_MOD_ALT)
			status[Alt] = true;
		if (flags & GLFW_MOD_SUPER)
			status[Mod] = true;
	}

	void ModifierStatus::setTo(ModifierStatus &m)
	{
		status[Shift] = m.status[Shift];
		status[Control] = m.status[Control];
		status[Alt] = m.status[Alt];
		status[Mod] = m.status[Mod];
	}

	void ModifierStatus::clear()
	{
		status[Shift] = status[Control] = status[Alt] = status[Mod] = false;
	}

	bool &ModifierStatus::shift()
	{
		return status[Shift];
	}

	bool &ModifierStatus::control()
	{
		return status[Control];
	}

	bool &ModifierStatus::alt()
	{
		return status[Alt];
	}

	bool &ModifierStatus::mod()
	{
		return status[Mod];
	}

	string ModifierStatus::toString()
	{
		stringstream ss;
		if (status[Control])
			ss << "+control";
		if (status[Shift])
			ss << "+shift";
		if (status[Alt])
			ss << "+alt";
		if (status[Mod])
			ss << "+mod";
		string s = ss.str();
		if (!s.empty())
			return s.substr(1);
		return "";
	}
}