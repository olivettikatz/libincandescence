#ifndef __LIB_INCANDESCENCE_UTIL_H
#define __LIB_INCANDESCENCE_UTIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#define INCD_MESSAGE_STREAM cout
#define INCD_MESSAGE_PREFIX "[Incandescence "<<__FILE__<<":"<<__LINE__<<"] "
#define INCD_MESSAGE_PREFIX_ERROR INCD_MESSAGE_PREFIX<<"error: "
#define INCD_MESSAGE_PREFIX_WARNING INCD_MESSAGE_PREFIX<<"warning: "
#define INCD_MESSAGE_PREFIX_DEBUG INCD_MESSAGE_PREFIX<<"debug: "
#define INCD_MESSAGE_PREFIX_TEST INCD_MESSAGE_PREFIX<<"test: "
#define INCD_MESSAGE_DISPLAY(msg) {INCD_MESSAGE_STREAM<<msg<<"\n";}

#define INCD_FATAL(msg) {INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_ERROR<<msg);throw std::runtime_error("internal incandescence error");}
#define INCD_ERROR(msg) {INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_ERROR<<msg);}
#define INCD_WARNING(msg) {INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_WARNING<<msg);}
#define INCD_DEBUG(msg) {INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_WARNING<<msg);}

#define INCD_TEST_HEADER(name) {INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_TEST<<"running '"<<name<<"'");}
#define INCD_TEST_ASSERT(expected, recieved) { \
	std::stringstream _ssExpected; \
	_ssExpected << expected; \
	std::stringstream _ssRecieved; \
	_ssRecieved << recieved; \
	if (_ssExpected.str().compare(_ssRecieved.str()) == 0) \
	{ \
		INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_TEST << "    '" << #expected << "' succeeded ('" << _ssExpected.str() << "' == '" << _ssRecieved.str() << "')."); \
	} \
	else \
	{ \
		INCD_MESSAGE_DISPLAY(INCD_MESSAGE_PREFIX_TEST << "    '" << #expected << "' failed ('" << _ssExpected.str() << "' != '" << _ssRecieved.str() << "')."); \
	} \
}

namespace incandescence
{
	using namespace std;

	bool fileExists(string path);
	string loadFile(string path);
}

#endif