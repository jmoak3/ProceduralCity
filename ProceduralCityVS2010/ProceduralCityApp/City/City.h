#include "../../D3DApp/Utility/Graphics/Graphics.h"
#include "../Building/BuildingManager.h"
#include "../Car/CarManager.h"
#include "../Plot/PlotManager.h"
#include "../Road/RoadManager.h"

#ifndef CITY_H
#define CITY_H

class City
{
public:
	City() {}
	~City() {}

	void init();

	void update(float dt);
	void draw(Graphics* g);


private:
	BuildingManager mBuildingManager;
	CarManager mCarManager;
	RoadManager mRoadManager;

	RectData mGround;
};

#endif