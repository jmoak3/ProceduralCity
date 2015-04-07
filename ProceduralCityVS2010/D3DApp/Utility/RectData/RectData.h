#include "../Vec/Vec.h"

#ifndef RECTDATA_H
#define RECTDATA_H

class RectData
{
public:
	RectData() 
			:x(0.0f), y(0.0f), z(0.0f),
			length(0.0f), width(0.0f), height(0.0f),
			c1(0.0f), c2(0.0f), c3(0.0f) {}
	RectData(float a, float b, float c,
				float l, float w, float h,
				float c11, float c22, float c33) 
			:x(a), y(b), z(c),
			length(l), width(w), height(h),
			c1(c11), c2(c22), c3(c33) {}
	RectData(Vec v, Vec lwh,
				float c11, float c22, float c33)
			:x(v.x), y(v.y), z(v.z),
			length(lwh.x), width(lwh.y), height(lwh.z),
			c1(c11), c2(c22), c3(c33) {}
	RectData(Vec v, Vec lwh, Vec col)
		:x(v.x), y(v.y), z(v.z),
		length(lwh.x), width(lwh.y), height(lwh.z),
		c1(col.x), c2(col.y), c3(col.z) {}

	~RectData() {}

	float x, y, z;
	float length, width, height;
	float c1, c2, c3;
};

#endif