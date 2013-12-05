#include "key.h"

namespace incandescence
{
	Key::Symbol Key::intToSymbol(int k)
	{
		switch(k)
		{
			case GLFW_KEY_UNKNOWN: return Null;
			case GLFW_KEY_SPACE: return Space;
			case GLFW_KEY_APOSTROPHE: return Apostrophe;
			case GLFW_KEY_COMMA: return Comma;
			case GLFW_KEY_MINUS: return Minus;
			case GLFW_KEY_PERIOD: return Period;
			case GLFW_KEY_SLASH: return Slash;
			case GLFW_KEY_0: return N0;
			case GLFW_KEY_1: return N1;
			case GLFW_KEY_2: return N2;
			case GLFW_KEY_3: return N3;
			case GLFW_KEY_4: return N4;
			case GLFW_KEY_5: return N5;
			case GLFW_KEY_6: return N6;
			case GLFW_KEY_7: return N7;
			case GLFW_KEY_8: return N8;
			case GLFW_KEY_9: return N9;
			case GLFW_KEY_SEMICOLON: return Semicolon;
			case GLFW_KEY_EQUAL: return Equal;
			case GLFW_KEY_A: return A;
			case GLFW_KEY_B: return B;
			case GLFW_KEY_C: return C;
			case GLFW_KEY_D: return D;
			case GLFW_KEY_E: return E;
			case GLFW_KEY_F: return F;
			case GLFW_KEY_G: return G;
			case GLFW_KEY_H: return H;
			case GLFW_KEY_I: return I;
			case GLFW_KEY_J: return J;
			case GLFW_KEY_K: return K;
			case GLFW_KEY_L: return L;
			case GLFW_KEY_M: return M;
			case GLFW_KEY_N: return N;
			case GLFW_KEY_O: return O;
			case GLFW_KEY_P: return P;
			case GLFW_KEY_Q: return Q;
			case GLFW_KEY_R: return R;
			case GLFW_KEY_S: return S;
			case GLFW_KEY_T: return T;
			case GLFW_KEY_U: return U;
			case GLFW_KEY_V: return V;
			case GLFW_KEY_W: return W;
			case GLFW_KEY_X: return X;
			case GLFW_KEY_Y: return Y;
			case GLFW_KEY_Z: return Z;
			case GLFW_KEY_LEFT_BRACKET: return BracketLeft;
			case GLFW_KEY_BACKSLASH: return Backslash;
			case GLFW_KEY_RIGHT_BRACKET: return BracketRight;
			case GLFW_KEY_GRAVE_ACCENT: return Accent;
			case GLFW_KEY_ESCAPE: return Escape;
			case GLFW_KEY_ENTER: return Enter;
			case GLFW_KEY_TAB: return Tab;
			case GLFW_KEY_BACKSPACE: return Backspace;
			case GLFW_KEY_INSERT: return Insert;
			case GLFW_KEY_DELETE: return Delete;
			case GLFW_KEY_RIGHT: return Right;
			case GLFW_KEY_LEFT: return Left;
			case GLFW_KEY_DOWN: return Down;
			case GLFW_KEY_UP: return Up;
			case GLFW_KEY_PAGE_UP: return PageUp;
			case GLFW_KEY_PAGE_DOWN: return PageDown;
			case GLFW_KEY_HOME: return Home;
			case GLFW_KEY_END: return End;
			case GLFW_KEY_CAPS_LOCK: return CapsLock;
			case GLFW_KEY_SCROLL_LOCK: return ScrollLock;
			case GLFW_KEY_NUM_LOCK: return NumLock;
			case GLFW_KEY_PRINT_SCREEN: return Print;
			case GLFW_KEY_PAUSE: return Pause;
			case GLFW_KEY_F1: return F1;
			case GLFW_KEY_F2: return F2;
			case GLFW_KEY_F3: return F3;
			case GLFW_KEY_F4: return F4;
			case GLFW_KEY_F5: return F5;
			case GLFW_KEY_F6: return F6;
			case GLFW_KEY_F7: return F7;
			case GLFW_KEY_F8: return F8;
			case GLFW_KEY_F9: return F9;
			case GLFW_KEY_F10: return F10;
			case GLFW_KEY_F11: return F11;
			case GLFW_KEY_F12: return F12;
			case GLFW_KEY_F13: return F13;
			case GLFW_KEY_F14: return F14;
			case GLFW_KEY_F15: return F15;
			case GLFW_KEY_F16: return F16;
			case GLFW_KEY_F17: return F17;
			case GLFW_KEY_F18: return F18;
			case GLFW_KEY_F19: return F19;
			case GLFW_KEY_F20: return F20;
			case GLFW_KEY_F21: return F21;
			case GLFW_KEY_F22: return F22;
			case GLFW_KEY_F23: return F23;
			case GLFW_KEY_F24: return F24;
			case GLFW_KEY_F25: return F25;
			case GLFW_KEY_KP_0: return K0;
			case GLFW_KEY_KP_1: return K1;
			case GLFW_KEY_KP_2: return K2;
			case GLFW_KEY_KP_3: return K3;
			case GLFW_KEY_KP_4: return K4;
			case GLFW_KEY_KP_5: return K5;
			case GLFW_KEY_KP_6: return K6;
			case GLFW_KEY_KP_7: return K7;
			case GLFW_KEY_KP_8: return K8;
			case GLFW_KEY_KP_9: return K9;
			case GLFW_KEY_KP_DECIMAL: return Decimal;
			case GLFW_KEY_KP_DIVIDE: return Divide;
			case GLFW_KEY_KP_MULTIPLY: return Multiply;
			case GLFW_KEY_KP_SUBTRACT: return Subtract;
			case GLFW_KEY_KP_ADD: return Add;
			case GLFW_KEY_KP_ENTER: return KEnter;
			case GLFW_KEY_LEFT_SHIFT: return ShiftLeft;
			case GLFW_KEY_LEFT_CONTROL: return ControlLeft;
			case GLFW_KEY_LEFT_ALT: return AltLeft;
			case GLFW_KEY_LEFT_SUPER: return ModLeft;
			case GLFW_KEY_RIGHT_SHIFT: return ShiftRight;
			case GLFW_KEY_RIGHT_CONTROL: return ControlRight;
			case GLFW_KEY_RIGHT_ALT: return AltRight;
			case GLFW_KEY_RIGHT_SUPER: return ModRight;
			case GLFW_KEY_MENU: return Menu;
			default: return Null;
		}
	}

	bool Key::isASCII()
	{
		return (value >= Space && value <= BracketRight) || (value >= Decimal && value <= KEnter) || (value >= N0 && value <= Z);
	}

	char Key::toASCII()
	{
		if (shift == false)
		{
			if (value >= N0 && value <= N9)
			{
				return '0'+(value-N0);
			}
			else if (value >= K0 && value <= K1)
			{
				return '0'+(value-K0);
			}
			else if (value >= A && value <= Z)
			{
				return 'a'+(value-A);
			}
			else
			{
				switch(value)
				{
					case Space: return ' ';
					case Escape: return '\x1b';
					case Enter: return '\n';
					case Tab: return '\t';
					case Backspace: return '\b';
					case Delete: return '\x7f';
					case Apostrophe: return '\'';
					case Comma: return ',';
					case Period: return '.';
					case Accent: return '`';
					case Minus: return '-';
					case Equal: return '=';
					case Slash: return '/';
					case Backslash: return '\\';
					case Semicolon: return ';';
					case BracketLeft: return '[';
					case BracketRight: return ']';
					case Decimal: return '.';
					case Divide: return '/';
					case Multiply: return '*';
					case Subtract: return '-';
					case Add: return '+';
					case KEnter: return '\r';
					default: return 0;
				}
			}
		}
		else
		{
			if (value >= K0 && value <= K1)
			{
				return '0'+(value-K0);
			}
			else if (value >= A && value <= Z)
			{
				return 'A'+(value-A);
			}
			else
			{
				switch(value)
				{
					case Space: return ' ';
					case Escape: return '\x1b';
					case Enter: return '\r';
					case Tab: return '\t';
					case Backspace: return '\b';
					case Delete: return '\x7f';
					case Apostrophe: return '\"';
					case Comma: return '<';
					case Period: return '>';
					case Accent: return '~';
					case Minus: return '_';
					case Equal: return '+';
					case Slash: return '?';
					case Backslash: return '|';
					case Semicolon: return ':';
					case BracketLeft: return '{';
					case BracketRight: return '}';
					case Decimal: return '.';
					case Divide: return '/';
					case Multiply: return '*';
					case Subtract: return '-';
					case Add: return '+';
					case KEnter: return '\r';
					case N1: return '!';
					case N2: return '@';
					case N3: return '#';
					case N4: return '$';
					case N5: return '%';
					case N6: return '^';
					case N7: return '&';
					case N8: return '*';
					case N9: return '(';
					case N0: return ')';
					default: return 0;
				}
			}
		}
	}

	string Key::toString()
	{
		stringstream ss;
		char a = toASCII();
		if (isprint(a))
			ss << a;
		else if (a != 0)
			ss << "\\x" << hex << (int)a;
		else
		{
			switch(value)
			{
				case Null: ss << "null"; break;
				case Up: ss << "up"; break;
				case Down: ss << "down"; break;
				case Left: ss << "left"; break;
				case Right: ss << "right"; break;
				case PageUp: ss << "pageup"; break;
				case PageDown: ss << "pagedown"; break;
				case Home: ss << "home"; break;
				case End: ss << "end"; break;
				case CapsLock: ss << "capslock"; break;
				case ScrollLock: ss << "scrolllock"; break;
				case NumLock: ss << "numlock"; break;
				case Print: ss << "print"; break;
				case Pause: ss << "pause"; break;
				case ShiftLeft: ss << "lshift"; break;
				case ShiftRight: ss << "rshift"; break;
				case ControlLeft: ss << "lcontrol"; break;
				case ControlRight: ss << "rcontrol"; break;
				case AltLeft: ss << "lalt"; break;
				case AltRight: ss << "ralt"; break;
				case ModLeft: ss << "lmod"; break;
				case ModRight: ss << "rmod"; break;
				case Menu: ss << "menu"; break;
				case F1: ss << "f1"; break;
				case F2: ss << "f2"; break;
				case F3: ss << "f3"; break;
				case F4: ss << "f4"; break;
				case F5: ss << "f5"; break;
				case F6: ss << "f6"; break;
				case F7: ss << "f7"; break;
				case F8: ss << "f8"; break;
				case F9: ss << "f9"; break;
				case F10: ss << "f10"; break;
				case F11: ss << "f11"; break;
				case F12: ss << "f12"; break;
				case F13: ss << "f13"; break;
				case F14: ss << "f14"; break;
				case F15: ss << "f15"; break;
				case F16: ss << "f16"; break;
				case F17: ss << "f17"; break;
				case F18: ss << "f18"; break;
				case F19: ss << "f19"; break;
				case F20: ss << "f20"; break;
				case F21: ss << "f21"; break;
				case F22: ss << "f22"; break;
				case F23: ss << "f23"; break;
				case F24: ss << "f24"; break;
				case F25: ss << "f25"; break;
				default: ss << "null"; break;
			}
		}
		return ss.str();
	}
}
