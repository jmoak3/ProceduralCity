#include <Windows.h>
#include "../D3DApp/Main/D3DApp.h"

#include "Building/BuildingManager.h"
#include "Car/CarManager.h"
#include "Plot/PlotManager.h"
#include "Road/RoadManager.h"
#include "City/City.h"

#ifndef PROCEDURALCITYAPP_H
#define	PROCEDURALCITYAPP_H


class ProceduralCityApp : public D3DApp
{
public:
	ProceduralCityApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY);
	~ProceduralCityApp();


	bool checkDeviceCaps();
	void lostGraphics();
	void resetGraphics();
	void update(float dt);
	void draw();

	void init();

private:
	City mCity;
};

#endif