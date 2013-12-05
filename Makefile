CXX=clang++
CXXFLAGS=-std=c++11 -O0 -g -Wall -Wno-write-strings
CXX_INCLUDES=-I/opt/X11/include -I/opt/local/include -I/opt/X11/include/freetype2
CXX_LIBS=-L/opt/local/lib -lfontconfig -lfreetype -framework OpengL -framework GLUT -lGLFW -lglew -lftgl

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

OBJ=util/Util.o util/GLUtil.o font/FontList.o font/FontRenderer.o audio/Sound.o audio/SoundExtern.o renderer/Window.o renderer/ModifierStatus.o renderer/Key.o renderer/Drawable.o renderer/Color.o renderer/Text.o renderer/Shader.o
TEST=util/TestUtil.o font/TestFontList.o audio/TestSoundExtern.o renderer/TestWindow.o renderer/TestDrawable.o renderer/TestOpenGL3.o renderer/TestOpenGL4.o renderer/TestOpenGL3Lib.o renderer/TestOpenGL4Lib.o

build : $(OBJ)

clean :
	rm -f $(shell echo *.o *.bin */*.o */*.bin)

test : $(TEST)
	for i in $(TEST); do echo $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); done
