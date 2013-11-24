CXX=clang++
CXXFLAGS=-std=c++11 -O0 -g -Wall -Wno-write-strings
CXX_INCLUDES=-I/opt/X11/include -I/opt/local/include
CXX_LIBS=-L/opt/local/lib -lfontconfig -lfreetype -framework OpengL -framework GLUT -lGLFW

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

OBJ=util/Util.o font/FontList.o audio/Sound.o audio/SoundExtern.o renderer/Window.o
TEST=util/TestUtil.o font/TestFontList.o audio/TestSoundExtern.o renderer/TestWindow.o

build : $(OBJ)

clean :
	rm -f $(shell echo *.o *.bin */*.o */*.bin)

test : $(TEST)
	for i in $(TEST); do echo $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); done
