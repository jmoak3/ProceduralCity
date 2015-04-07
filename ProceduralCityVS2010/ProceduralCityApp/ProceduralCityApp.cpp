#include "ProceduralCityApp.h"

ProceduralCityApp::ProceduralCityApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY) : D3DApp(hInstance, winCaption, screenX, screenY)
{

}

ProceduralCityApp::~ProceduralCityApp()
{
	
}

void ProceduralCityApp::init()
{
	mCity.init();
}

bool ProceduralCityApp::checkDeviceCaps()
{
	return true;
}

void ProceduralCityApp::lostGraphics()
{
	mGraphics.lostDevice();
}

void ProceduralCityApp::resetGraphics()
{
	mGraphics.resetDevice();
}

void ProceduralCityApp::update(float dt)
{
	mGraphics.updateStats(dt);
	mInput.poll();
	//^Call these before anything else^


	mCity.update(dt);

	
	//Call last
	mGraphics.updateCamera(dt, &mInput);
}

void ProceduralCityApp::draw()
{
	mCity.draw(&mGraphics);

	//Call Last
	mGraphics.draw();
}