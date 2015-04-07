#include "../../D3DApp/Utility/Graphics/Graphics.h"
#include <vector>
#include "Car.h"

#ifndef CARMANAGER_H
#define CARMANAGER_H

class CarManager
{
public:
	CarManager() {}
	~CarManager() {}

	void init(float speed, int numCars, float roadWidth);

	void update(float dt);
	void draw(Graphics* g);

	void addTurns(float x, float z, float roadwidth);

	std::vector<Car> getCars();

private:
	float mCarSpeed;
	//carlist
	std::vector<Car> mCarList;

	std::vector<Turn> mTurnList;
};

#endif