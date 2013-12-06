#include "../util/GLUtil.h"
#include "../font/FontRenderer.h"
#include "Window.h"
#include "Poly.h"
#include "Text.h"

using namespace incandescence;

FontRenderer font;

class Test : public Window
{
public:
	Poly<Drawable::StrokedPoly> poly;
	Text text;
	void loadHandler();
	void renderHandler();
};

void Test::loadHandler()
{
	poly.color = Color(255, 0, 0);
	poly.vertex(10, 10);
	poly.vertex(50, 10);
	poly.vertex(50, 50);
	poly.vertex(10, 50);
	poly.load(*this);

	text = Text("hello, world", 20, 50, font);
	text.color = Color(255, 0, 0);
	text.load(*this);
}

void Test::renderHandler()
{
	useShader(INCD_SHADER_2D);
	poly.render(*this);

	useShader(INCD_SHADER_TEXT);
	text.render(*this);
}

int main()
{
	INCD_TEST_HEADER("Test::exec");
	initGL(4, 1);
	initFontRendering();
	Test t;
	t.init();
	t.setSize(200, 200);
	t.setTitle("test");
	font = FontRenderer("/System/Library/Fonts/Monaco.dfont", 48);
	font.setDPI(getDPI());
	font.load3D(t);
	INCD_TEST_ASSERT(font.good(), true);
	t.exec();
	INCD_TEST_ASSERT(true, true);
}
