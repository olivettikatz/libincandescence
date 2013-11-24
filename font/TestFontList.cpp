#include "FontList.h"

using namespace incandescence;

int main()
{
	INCD_TEST_HEADER("FontList::populate");
	FontList fl;
	fl.populate();
	INCD_TEST_ASSERT(fl.names().empty(), false);
	INCD_TEST_ASSERT(fl.paths().empty(), false);
	return 0;
}