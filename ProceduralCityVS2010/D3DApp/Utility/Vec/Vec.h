#ifndef VEC_H
#define VEC_H


class Vec
{
public:
	Vec() :x(0.0f), y(0.0f), z(0.0f) {};
	Vec(float a, float b, float c) :x(a), y(b), z(c) {};

	~Vec() {};


	float x, y, z;
};

#endif