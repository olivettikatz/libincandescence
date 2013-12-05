#include "../util/GLUtil.h"
#include "Window.h"
#include "Poly.h"
#include "Text.h"
#include "../font/FontRenderer.h"

using namespace incandescence;

FontRenderer font;

class Test : public Window
{
public:
	Poly<Drawable::StrokedPoly> poly;
	Text text;
	int shader2D, shaderText;
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

	shader2D = loadShader("VertexShader2D.glsl", "FragmentShader2D.glsl");
	if (getShader(shader2D).good() == false)
		INCD_FATAL("could not load 2d shader");
	shaderText = loadShader("VertexShaderText.glsl", "FragmentShaderText.glsl");
	if (getShader(shaderText).good() == false)
		INCD_FATAL("could not load text shader");
}

void Test::renderHandler()
{
	useShader(shader2D);
	poly.render(*this);

	useShader(shaderText);
	text.render(*this);
}

int main()
{
	INCD_TEST_HEADER("Test::exec");
	INCD_TEST_ASSERT(font.good(), true);
	initGL(4, 1);
	initFontRendering();
	Test t;
	t.init();
	t.setSize(200, 200);
	t.setTitle("test");
	font = FontRenderer("/System/Library/Fonts/Monaco.dfont", 48);
	font.setDPI(getDPI());
	font.load3D(t.getShader(1).getPid());
	t.exec();
	INCD_TEST_ASSERT(true, true);
}
