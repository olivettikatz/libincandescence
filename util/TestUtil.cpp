#include "Util.h"

using namespace incandescence;

int main(int argc, char *argv[])
{
	INCD_TEST_HEADER("fileExists");
	INCD_TEST_ASSERT(fileExists(argv[0]), true);
	return 0;
}