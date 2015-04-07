#include "CarManager.h"
#include <ctime>

inline float GetRandFloat()
{
	float r;
	r = (rand() % 10001) * 0.0001f;
	return r;
}

void CarManager::init(float speed, int numCars, float roadWidth)
{
	for (int i=0;i<numCars;++i)
	{
		Car newCar(speed, 20.0f, 10.0f, 10.0f);
		Vec newPos = Vec(0.8f*roadWidth, 10.0f, 40.0f*i + 50.0f);
		newCar.setPos(newPos);
		mCarList.push_back(newCar);
	}
}

bool intersect(float x1, float z1, float x2, float z2,
				float a, float b)
{
	//lataa

	return false;
}

bool intersect(float x, float z, float a, float b)
{
	//approx this TODO
	if (x == a && z == b)
		return true;

	float dist;
	dist = powf((powf((a - x), 2.000f) + powf((b - z), 2.000f)), 1.000f/2.000f);
	if (dist < 7.0f && dist > -7.0f)
		return true;

	return false;
}

void CarManager::update(float dt)
{
	for (int i=0;i<mCarList.size();++i)
	{
		mCarList[i].update(dt);
		//if car in turn
		for (int j=0;j<mTurnList.size();++j)
		{
			//if (intersect(mCarList[i].getX()-mCarList[i].getLength()*0.5f, mCarList[i].getZ()-mCarList[i].getWidth()*0.5f, 
			//	mCarList[i].getX()+mCarList[i].getLength()*0.5f, mCarList[i].getZ()+mCarList[i].getWidth()*0.5f,
			//			mTurnList[j].x+mTurnList[j].width*0.5f, mTurnList[j].z+mTurnList[j].width*0.5f))
			if (intersect(mCarList[i].getX(), mCarList[i].getZ(),
					mTurnList[j].x+mTurnList[j].width*0.5f, mTurnList[j].z+mTurnList[j].width*0.5f))
			{
				if (!mCarList[i].hasTurned() && GetRandFloat()*5.0f > 2.5f)
				{
					if (!mCarList[i].hasSecondTurn())
					{
						mCarList[i].rotate(mTurnList[j].rotation,
						mTurnList[j].x+mTurnList[j].width*0.5f, 
						mTurnList[j].z+mTurnList[j].width*0.5f);
					}
					else if (mCarList[i].hasSecondTurn() && (
						mTurnList[j].x != mCarList[i].getTurnPassed().x ||
						mTurnList[j].z != mCarList[i].getTurnPassed().z ))
					{
						mCarList[i].rotate(-1.0f*(mTurnList[j].rotation),
						mTurnList[j].x+mTurnList[j].width*0.5f, 
						mTurnList[j].z+mTurnList[j].width*0.5f);
					}
				}
				else
				{
					mCarList[i].doSecondTurn();
					if (mCarList[i].getTurnPassed().width < -400)
						mCarList[i].setTurnPassed(mTurnList[j]);
				}
			}
		}
	}
}

void CarManager::draw(Graphics* g)
{
	for (int i=0;i<mCarList.size();++i)
	{
		mCarList[i].draw(g);
	}
}

std::vector<Car> CarManager::getCars()
{
	return mCarList;
}


void CarManager::addTurns(float x, float z, float width)
{
	//make 4 turns.
	Turn turn;
	turn.x = x;
	turn.z = z;
	turn.width = width/2.0f;
	turn.rotation = -3.14159f*0.5f;
	mTurnList.push_back(turn);

	Turn turn2;
	turn2.x = x+width/2.0f;
	turn2.z = z;
	turn2.width = width/2.0f;
	turn2.rotation = -3.14159f*0.5f;
	mTurnList.push_back(turn2);

	Turn turn3;
	turn3.x = x;
	turn3.z = z+width/2.0f;
	turn3.width = width/2.0f;
	turn3.rotation = -3.14159f*0.5f; 
	mTurnList.push_back(turn3);

	Turn turn4;
	turn4.x = x+width/2.0f;
	turn4.z = z+width/2.0f;
	turn4.width = width/2.0f;
	turn4.rotation = -3.14159f*0.5f;
	mTurnList.push_back(turn4);
}

