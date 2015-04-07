#include "BuildingManager.h"
#include <ctime>
#include <math.h>

inline float GetRandFloat()
{
	float r;
	r = (rand() % 10001) * 0.0001f;
	return r;
}

void BuildingManager::init(float minHeight, float maxHeight, float minWidth)
{
	srand((unsigned int)time(NULL));

	mMinHeight = minHeight;
	mMaxHeight = maxHeight;
	mMinWidth = minWidth;
}

void BuildingManager::addBuilding(float x, float y, float z, float l, float w)
{	float height = 1.0f;
	float width = w+1.0f;

	//TODO implement length
	float e = w;
	if (l < w) e = l;
	while (e > mMinWidth)
	{
		height = GetRandFloat()*mMaxHeight+mMinHeight;
		while (width > e)
		{
			width = GetRandFloat()*(e-mMinWidth) + mMinWidth;
		}

		float color = GetRandFloat()*0.4f;
		if (e==l || e==w) x += (width*0.5f);
		if (e==l || e==w) z += (width*0.5f);
		y += height;
		RectData building(	x, y, z,
							width*0.5f, height, width*0.5f,
							color, color, color);
		mBuildingList.push_back(building);
		e = width*(0.8f);
		y+= height;
	}
}

void BuildingManager::addPlot(float x, float z, float x2, float z2)
{
	Plot newPlot;
	newPlot.x1 = x;
	newPlot.z1 = z;
	newPlot.x2 = x2;
	newPlot.z2 = z2;

	mPlotList.push_back(newPlot);
}

void BuildingManager::populate()
{
	for (int i=0;i<mPlotList.size();++i)
	{
		Plot p = mPlotList[i];

		//addBuilding(p.x1, 1.0f, p.z1, abs(p.x2-p.x1), abs(p.z2-p.z1));
		float spaceX = GetRandFloat()*(abs(p.x2-p.x1)/2.0f);
		float spaceZ = GetRandFloat()*(abs(p.z2-p.z1)/2.0f);
		addBuilding(spaceX + p.x1,
					1.0f,
					spaceZ + p.z1,
					abs(p.x2-p.x1)-spaceX,
					abs(p.z2-p.z1)-spaceZ);
	}
}

float BuildingManager::getWidth()
{
	return mMinWidth;
}

void BuildingManager::update(float dt)
{

}

void BuildingManager::draw(Graphics* g)
{
	for (int i=0;i<mBuildingList.size();++i)
		g->addRect(mBuildingList[i]);
}