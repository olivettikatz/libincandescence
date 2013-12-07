# Copyright 2013 Oliver Katz
#
# This file is part of LibIncandescence.
#
# LibIncandescence is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# LibIncandescene is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with LibIncandescence.  If not, see <http://www.gnu.org/licenses/>.

CXX=clang++
CXXFLAGS=-std=c++11 -O0 -g -Wall -Wno-write-strings
CXX_INCLUDES=-I/opt/X11/include -I/opt/local/include -I/opt/X11/include/freetype2
CXX_LIBS=-L/opt/local/lib -lfontconfig -lfreetype -framework OpengL -framework GLUT -lGLFW -lglew -lftgl

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

OBJ=util/Util.o util/GLUtil.o font/FontList.o font/FontRenderer.o audio/Sound.o audio/SoundExtern.o renderer/Window.o renderer/ModifierStatus.o renderer/Key.o renderer/Drawable.o renderer/Color.o renderer/Text.o renderer/Shader.o renderer/Framebuffer.o
TEST=util/TestUtil.o font/TestFontList.o audio/TestSoundExtern.o renderer/TestWindow.o renderer/TestDrawable.o renderer/TestOpenGL3.o renderer/TestOpenGL4.o renderer/TestOpenGL3Lib.o renderer/TestOpenGL4Lib.o

build : $(OBJ)

clean :
	rm -rf $(shell echo *.o *.bin */*.o */*.bin) doc/html

test : $(TEST)
	for i in $(TEST); do echo $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); done

doxygen :
	doxygen doxygen.cfg
	cp customTabs.css doc/html/tabs.css