#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../util/GLUtil.h"
#include "Window.h"
#include "Poly.h"

using namespace incandescence;

class Test : public Window
{
public:
    Poly<Drawable::StrokedPoly> poly;
    void loadHandler();
    void renderHandler();
};

void Test::loadHandler()
{
    poly.color = Color(255, 0, 0);
    poly.vertex(0, 0);
    poly.vertex(200, 0);
    poly.vertex(100, 200);
    poly.load(*this);
}

void Test::renderHandler()
{
    poly.render(*this);
}

int main()
{
    initGL(4, 1);

    Test t;
    t.init();
    t.exec();

    return 0;
}
