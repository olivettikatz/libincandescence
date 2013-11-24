#include "Window.h"

using namespace incandescence;

int main()
{
	INCD_TEST_HEADER("Window::exec");
	Window w;
	w.setSize(200, 200);
	w.setTitle("test");
	Window::initGlobal();
	w.init();
	w.exec();
	Window::haltGlobal();
	INCD_TEST_ASSERT(true, true);
	return 0;
}