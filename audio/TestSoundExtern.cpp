#include "SoundLoader.h"
#include "SoundExtern.h"

using namespace incandescence;

int main(int argc, char *argv[])
{
	INCD_TEST_HEADER("SoundExtern::play");
	INCD_TEST_ASSERT(argc, 2);
	SoundLoader<SoundExtern> loader;
	loader.add("bell", argv[1]);
	loader.loadAll();
	loader.play("bell");
	INCD_TEST_ASSERT(true, true);
	return 0;
}