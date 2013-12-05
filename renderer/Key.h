#ifndef __LIB_INCANDESCENCE_KEY_H
#define __LIB_INCANDESCENCE_KEY_H

#include "../util/Util.h"
#include "ModifierStatus.h"

namespace incandescence
{
	using namespace std;

	class Key
	{
	public:
		typedef enum
		{
			Null,
			Space, Escape, Enter, Tab, Backspace, Insert, Delete,
			Apostrophe, Comma, Period, Accent,
			Minus, Equal,
			Slash, Backslash,
			Semicolon,
			BracketLeft, BracketRight,
			Up, Down, Left, Right,
			PageUp, PageDown, Home, End,
			CapsLock, ScrollLock, NumLock, Print, Pause,
			Decimal, Divide, Multiply, Subtract, Add, KEnter,
			ShiftLeft, ShiftRight, ControlLeft, ControlRight, AltLeft, AltRight, ModLeft, ModRight, Menu,
			N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
			K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25
		} Symbol;

		Symbol value;
		bool shift;

	protected:
		Symbol intToSymbol(int k);

	public:
		Key() : value(Null) {}
		Key(int k, bool s = false) : value(intToSymbol(k)), shift(s) {}
		bool isASCII();
		char toASCII();
		string toString();
	};
}

#endif