#include "../../D3DApp/Utility/Vec/Vec.h"
#include "../../D3DApp/Utility/Graphics/Graphics.h"

#ifndef CAR_H
#define CAR_H

struct Turn 
{
	float x;
	float z;
	float width;
	float rotation;
};

class Car
{
public:
	Car(float speed, float l, float w, float h);
	~Car();

	void update(float dt);
	void draw(Graphics * g);

	void move(float dt);
	void rotate(float rot, float x, float z);

	void verifyRotation();

	void setPos(float x, float y, float z);

	void setPos(Vec vec);

	float getX();
	float getZ();

	bool hasTurned();
	bool hasSecondTurn();
	void doSecondTurn();

	Turn getTurnPassed();
	void setTurnPassed(Turn turn);

private:
	Vec mDir;
	Vec mPos;
	float mRotation;
	float mSetLength;
	float mSetWidth;
	float mSetHeight;
	float mCurrLength;
	float mCurrWidth;
	float mCurrHeight;
	float mSpeed;
	float mTurnTimer;
	float mTurnTime;
	bool mTurned;
	bool mSecondTurn;

	Turn mTurnPassed;
};

#endif