#include "../../D3DApp/Utility/Graphics/Graphics.h"
#include "../../D3DApp/Utility/RectData/RectData.h"

#include <vector>

#ifndef BUILDINGMANAGER_H
#define BUILDINGMANAGER_H

struct Plot
{
	float x1;
	float x2;
	float z1;
	float z2;
};

class BuildingManager
{
public:
	BuildingManager() {}
	~BuildingManager() {}

	void init(float minHeight, float maxHeight, float minWidth);

	float getWidth();	

	void update(float dt);
	void draw(Graphics* g);

	void addBuilding(float x, float y, float z, float l, float w);

	void addPlot(float x, float z, float x2, float z2);

	void populate();

private:
	//list of turns
	//roadlist
	float mMinHeight;
	float mMinWidth;

	float mMaxHeight;

	std::vector<Plot> mPlotList;
	std::vector<RectData> mBuildingList;
};

#endif