#include "Car.h"

Car::Car(float speed, float l, float w, float h)
{
	mSpeed = speed;
	mSetLength = l;
	mSetWidth = w;
	mSetHeight = h;
	mCurrLength = 0.0f;
	mCurrWidth = 0.0f;
	mCurrHeight = 0.0f;
	mPos.x = 0.0f;
	mPos.y = 10.0f;
	mPos.z = 0.0f;
	mRotation = 0.0f;
	mTurnTime = 0.0f;
	mTurnTimer = 4.0f;
	mTurned = false;
	mSecondTurn = false;

	mTurnPassed.width = -500;
	mTurnPassed.x = -99999;
	mTurnPassed.z = -99999;
}

Car::~Car()
{

}

void Car::update(float dt)
{
	mTurnTime += dt;
	if (mTurnTime > mTurnTimer)
	{
		mTurned = false;
		mSecondTurn = false;
		mTurnPassed.width = -500;
		mTurnPassed.x = -99999;
		mTurnPassed.z = -99999;
		mTurnTime = 0.0f;
	}
	verifyRotation();
	move(dt);
}

void Car::draw(Graphics * g)
{
	g->addRect(mPos.x, mPos.y, mPos.z, 
				mCurrWidth/2.0f, mCurrHeight, mCurrLength/2.0f,
				1.0f, 1.0f, 1.0f);
}

void Car::move(float dt)
{
	mPos.x += mDir.x*mSpeed*dt;
	mPos.y += mDir.y*mSpeed*dt;
	mPos.z += mDir.z*mSpeed*dt;
}

void Car::rotate(float rot, float x, float z)
{
	mRotation += rot;
	mPos.x = x;
	mPos.z = z;
	if (mRotation > 6.283)
		mRotation -= 6.283;
	if (mRotation < 0.0f)
		mRotation += 6.283;

	if (mRotation < 1.0f && mRotation > -1.0f)
	{
		mCurrLength = mSetLength;
		mCurrWidth = mSetWidth;
		mCurrHeight = mSetHeight;
		mRotation = 0.0f;
	}

	if (mRotation < 3.14159f+0.5f && mRotation > 3.14159f-0.5f)
	{
		mCurrLength = mSetLength;
		mCurrWidth = mSetWidth;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f;
	}


	if (mRotation < 3.14159f/2.0f+0.5f && mRotation > 3.14159f/2.0f-0.5f)
	{
		mCurrLength = mSetWidth;
		mCurrWidth = mSetLength;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f/2.0f;
	}

	if (mRotation < 3.14159f*3.0f/2.0f+0.5f && mRotation > 3.14159f*3.0f/2.0f-0.5f)
	{
		mCurrLength = mSetWidth;
		mCurrWidth = mSetLength;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f*3.0f/2.0f;
	}

	mDir = Vec(-sinf(mRotation), 0.0f, cosf(mRotation));

	mTurned = true;
}

void Car::verifyRotation()
{
	if (mRotation > 6.283)
		mRotation -= 6.283;
	if (mRotation < 0.0f)
		mRotation += 6.283;

	if (mRotation < 0.5f && mRotation > -0.5f)
	{
		mCurrLength = mSetLength;
		mCurrWidth = mSetWidth;
		mCurrHeight = mSetHeight;
		mRotation = 0.0f;
	}

	if (mRotation < 3.14159f+0.5f && mRotation > 3.14159f-0.5f)
	{
		mCurrLength = mSetLength;
		mCurrWidth = mSetWidth;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f;
	}


	if (mRotation < 3.14159f/2.0f+0.5f && mRotation > 3.14159f/2.0f-0.5f)
	{
		mCurrLength = mSetWidth;
		mCurrWidth = mSetLength;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f/2.0f;
	}

	if (mRotation < 3.14159f*3.0f/2.0f+0.5f && mRotation > 3.14159f*3.0f/2.0f-0.5f)
	{
		mCurrLength = mSetWidth;
		mCurrWidth = mSetLength;
		mCurrHeight = mSetHeight;
		mRotation = 3.14159f*3.0f/2.0f;
	}

	mDir = Vec(-sinf(mRotation), 0.0f, cosf(mRotation));
}

void Car::setPos(float x, float y, float z)
{
	mPos.x = x;
	mPos.y = y;
	mPos.z = z;
}

void Car::setPos(Vec vec)
{
	Car::setPos(vec.x, vec.y, vec.z);
}

float Car::getX()
{
	return mPos.x;
}

float Car::getZ()
{
	return mPos.z;
}

bool Car::hasTurned()
{
	//bool turn = mTurned;
	return mTurned;
}

bool Car::hasSecondTurn()
{
	return mSecondTurn;
}

void Car::doSecondTurn()
{
	mSecondTurn = true;
}

Turn Car::getTurnPassed()
{
	return mTurnPassed;
}

void Car::setTurnPassed(Turn turn)
{
	mTurnPassed = turn;
}