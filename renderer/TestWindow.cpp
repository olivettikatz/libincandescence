#include "Window.h"

using namespace incandescence;

int main()
{
	INCD_TEST_HEADER("Window::exec");
	Window w;
	w.setSize(200, 200);
	w.setTitle("test");
	initGL();
	w.init();
	w.exec();
	haltGL();
	INCD_TEST_ASSERT(true, true);
	return 0;
}