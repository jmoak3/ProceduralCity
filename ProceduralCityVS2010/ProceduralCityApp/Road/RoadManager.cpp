#include "RoadManager.h"

void RoadManager::init(float width, float maxSizeX, float maxSizeZ)
{
	mWidth = width;
	mMaxSizeX = maxSizeX;
	mMaxSizeZ = maxSizeZ;
}

void RoadManager::addRoadX(float x)
{
	mRoadList.push_back(RectData(x+(mWidth*0.5f), 1.0f, 0.0f,
								mWidth*0.5f, 10.0f, mMaxSizeZ*0.5f,
								0.25f, 0.25f, 0.25f));
}

void RoadManager::addRoadZ(float z)
{
	mRoadList.push_back(RectData(0.0f, 1.0f, z+(mWidth*0.5f),
								mMaxSizeX*0.5f, 10.0f, mWidth*0.5f,
								0.25f, 0.25f, 0.25f));
}

void RoadManager::addRoad(float x, float z, float l, float w)
{

}

float RoadManager::getWidth()
{
	return mWidth;
}

void RoadManager::setWidth(float width)
{
	mWidth = width;
}


void RoadManager::update(float dt)
{

}

void RoadManager::draw(Graphics* g)
{
	for (int i=0;i<mRoadList.size();++i)
		g->addRect(mRoadList[i]);
}

