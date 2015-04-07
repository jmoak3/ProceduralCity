#include "../../D3DApp/Utility/Graphics/Graphics.h"
#include "../../D3DApp/Utility/RectData/RectData.h"
#include <vector>

#ifndef ROADMANAGER_H
#define ROADMANAGER_H

class RoadManager
{
public:
	RoadManager() {}
	~RoadManager() {}

	void init(float width, float mMaxSizeX, float mMaxSizeZ);

	float getWidth();
	void setWidth(float width);

	void update(float dt);
	void draw(Graphics* g);

	void addRoadX(float x);
	void addRoadZ(float z);
	void addRoad(float x, float z, float l, float w);

private:
	//list of turns
	//roadlist
	std::vector<RectData> mRoadList;
	float mWidth;
	float mMaxSizeX;
	float mMaxSizeZ;
};

#endif