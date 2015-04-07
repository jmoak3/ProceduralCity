#include "City.h"
#include <ctime>

inline float GetRandFloat()
{
	float r;
	r = (rand() % 10001) * 0.0001f;
	return r;
}


void City::init()
{
	float sizeX=15000.0f;
	float sizeZ=15000.0f;

	srand((unsigned int)time(NULL));

	const int divis = 20;

	float dist = sizeX/(float)(divis); //distance between roads

	mGround = RectData(0.0f, 1.0f, 0.0f, 
						sizeX*0.5f, 0.0f, sizeZ*0.5f,
						0.0f, 1.0f, .25f);

	mBuildingManager.init(150.0f, 1000.0f, 250.0f);
	mRoadManager.init(50.0f, sizeX, sizeZ);
	
	float roadWidth = mRoadManager.getWidth();

	mCarManager.init(50.0f, 50, roadWidth);
	float currZ = -(sizeZ*0.5f);
	float currX = -(sizeX*0.5f);


	const int divs = divis+1;

	bool roadX[divs];
	bool roadZ[divs];
	for (int i=0;i<divs;++i)
		roadX[i] = false;
	roadX[divs-1] = true;
	for (int i=0;i<divs;++i)
		roadZ[i] = false;
	roadZ[divs-1] = true;
	
	//TODO implement more on x direction
	
	int zs = 0;
	while (currZ <= sizeZ*0.5f)
	{
		int xs = 0;
		while (currX <= sizeX*0.5f)
		{
			if (GetRandFloat()>0.0f)
			{
				mRoadManager.addRoadX(currX);
				roadX[xs] = true;
				if (xs < divs-1) ++xs;
			}
			currX+=dist;
		}

		if (GetRandFloat()>0.0f)
		{
			mRoadManager.addRoadZ(currZ);
			roadZ[zs] = true;
			if (zs < divs-1) ++zs;

		}
		currZ+=dist;
	}

	int lastX = 0;
	int lastZ = 0;
	bool done = false;
	int I = 1;
	int J = 1;
	while (!done)
	{
		while(I != divs && !roadX[I])
		{
			++I;	
		}

		while(!(J >= divs) && !roadZ[J])
		{
			++J;
		}

		if (I != divs)
			mBuildingManager.addPlot(lastX*dist - (0.5f*sizeX) + roadWidth, 
									lastZ*dist - (0.5f*sizeZ) + roadWidth,
									(I)*dist - (0.5f*sizeX) - roadWidth, 
									(J)*dist - (0.5f*sizeZ) - roadWidth);
	
		lastX = I;

		//find new road
		//is j, our bottom.
		//the road before is lastZ until next j

		++I;

		if (I >= divs && J >= divs-1)
			done = true;

		if (I >= divs && !(J >= divs-1))
		{
			lastX = 0;
			lastZ = J;
			++J;
			I = 1;
		}
	}

	mBuildingManager.populate();

	//if intersection spawn 4 turn spots
	//Half x, half z of road.
	/*
	      | |
	   ---# #---
	   ---# #---
		  | |
	*/
	//Each turn spot will have the amount it will turn the car by.
	//These belong to car manager
	//on collide with car spot, run 50/50 chance to turn by carspot's amount.
	//(Wont be proofed for irregular road patterns!!)
	
	for (int i=0;i<divs;++i) 
	{
		for (int j=0;j<divs;++j)
		{
			if (roadZ[i] && roadX[j])
			{
				mCarManager.addTurns( (j)*dist - (0.5f*sizeX), (i)*dist - (0.5f*sizeZ), 
									  roadWidth);
			}
		}
	}
	mCarManager.addTurns( (divs)*dist - (0.5f*sizeX), (divs)*dist - (0.5f*sizeZ), 
						 roadWidth);	
}

void City::update(float dt)
{
	
	mCarManager.update(dt);
}

void City::draw(Graphics* g)
{
	mBuildingManager.draw(g);
	mRoadManager.draw(g);
	mCarManager.draw(g);

	g->addRect(mGround);
}

