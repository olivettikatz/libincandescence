/* Copyright 2013 Oliver Katz
 *
 * This file is part of LibIncandescence.
 *
 * LibIncandescence is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibIncandescene is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibIncandescence.  If not, see <http://www.gnu.org/licenses/>.
 */

 /*! \file Util.h
  *  \brief Basic utilities for all of LibIncandescence.
  *  Util.h contains console message formatting, macros to display debug messages,
  *  warnings, non-fatal errors and fatal errors. It also contains the testing system,
  *  which is very primitive, but hey. Lastly, it contains file IO for the basic loading
  *  of configuration/script files. */

/*! \def INCD_MESSAGE_STREAM
 *  \brief The IO stream to output console messages to.
 *  This can easily be changed to cerr, if stdout conflicts with other messages. */

/*! \def INCD_MESSAGE_PREFIX
 *  \brief The prefix to use for all console messages.
 *  Contains the file and line number location that the message originated from. */

/*! \def INCD_MESSAGE_PREFIX_ERROR
 *  \brief The prefix to use for all errors. */

/*! \def INCD_MESSAGE_PREFIX_WARNING
 *  \brief The prefix to use for all warnings. */

/*! \def INCD_MESSAGE_PREFIX_DEBUG
 *  \brief The prefix to use for all debug messages. */

/*! \def INCD_MESSAGE_PREFIX_TEST
 *  \brief The prefix to use for all test message. */

/*! \def INCD_MESSAGE_DISPLAY(msg)
 *  \brief Displays text in \a msg to console. 
 *  Displays text with no prefix to stream defined in INCD_MESSAGE_STREAM. */

/*! \def INCD_FATAL(msg)
 *  \brief Displays fatal error to console, then halts program.
 *  After it displays the fatal error, it will throw a std::runtime_error
 *  exception, so that the source of the fatal error may be backtraced
 *  with a debugger. */

/*! \def INCD_ERROR(msg)
 *  \brief Displays error to console, but doesn't halt program.
 *  Fun fact: the output to the console is identical to that of INCD_FATAL. */

/*! \def INCD_WARNING(msg)
 *  \brief Displays a warning to console. */

/*! \def INCD_DEBUG(msg)
 *  \brief Displays a debug message to console. */

/*! \def INCD_TEST_HEADER(name)
 *  \brief Denotes the beginning of a test.
 *  When you are testing something in a test file, use this at the beginning of a test
 *  to tell the user that a new test is starting.
 *
 *  For example:
 *  \include TestUtil.cpp */

/*! \def INCD_TEST_ASSERT(expected, recieved)
 *  \brief Displays the result of a test.
 *  Displays the value of \a expected and \a recieved, as well as the code for \a recieved
 *  so that the user can see what the test was for. */

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

/*! Namespace for all LibIncandescence classes/methods/global variables. */
namespace incandescence
{
	using namespace std;

	/*! Tests to see if a file exists.
	 *  \param path The path of the file. */
	bool fileExists(string path);

	/*! Reads the contents of a text file into memory and returns it as a string.
	 *  \param path The path of the file. */
	string loadFile(string path);
}

#endif