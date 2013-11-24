CXX=clang++
CXXFLAGS=-std=c++11 -O0 -g -Wall -Wno-write-strings
CXX_INCLUDES=-I/opt/local/include/fontconfig -I/opt/X11/include
CXX_LIBS=-L/opt/local/lib -lfontconfig -lfreetype -framework OpengL -framework GLUT -lGLFW

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXX_INCLUDES)

OBJ=util/Util.o font/FontList.o audio/Sound.o audio/SoundExtern.o
TEST=util/TestUtil.o font/TestFontList.o audio/TestSoundExtern.o

build : $(OBJ)

clean :
	rm -f $(OBJ)

test : $(TEST)
	for i in $(TEST); do echo $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); $(CXX) $(CXXFLAGS) $$i $(OBJ) -o $$(dirname $$i)/$$(basename $$i .o).bin $(CXX_INCLUDES) $(CXX_LIBS); done
