#include "TestApp.h"

TestApp::TestApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY) : D3DApp(hInstance, winCaption, screenX, screenY)
{

}

TestApp::~TestApp()
{
	
}

void TestApp::init()
{
	RectData rd(0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd2(0.0f, 2.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd7(0.0f, 4.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd3(2.0f, 2.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd4(4.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd5(4.0f, 2.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd6(4.0f, 4.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f);

	RectData rd8(8.0f, 4.0f, 0.0f,
		0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 0.0f);

	RectData rd9(8.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f);

	RectData rd10(8.0f, 2.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f);
	mGraphics.addRect(rd);
	mGraphics.addRect(rd2);
	mGraphics.addRect(rd3);
	mGraphics.addRect(rd4);
	mGraphics.addRect(rd5);
	mGraphics.addRect(rd6);
	mGraphics.addRect(rd7);
	mGraphics.addRect(rd8);
	mGraphics.addRect(rd9);
	mGraphics.addRect(rd10);

}

bool TestApp::checkDeviceCaps()
{
	return true;
}

void TestApp::lostGraphics()
{
	mGraphics.lostDevice();
}

void TestApp::resetGraphics()
{
	mGraphics.resetDevice();
}

void TestApp::update(float dt)
{
	int x = 0;
	x = x + 5;
}

void TestApp::draw()
{
	mGraphics.draw();
}