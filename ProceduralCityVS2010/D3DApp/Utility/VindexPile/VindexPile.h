//Has list with all vertices in it
//Has list with all indices in it
//Singleton!!!!

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <vector>

#include "../Vertex/Vertex.h"
#include "../RectData/RectData.h"

#ifndef VINDEXPILE_H
#define VINDEXPILE_H




class VindexPile
{
public:
	VindexPile();
	~VindexPile();

	void init(IDirect3DDevice9* d3dDevice);

	void addRect(float x, float y, float z,
		float length, float width, float height,
		float c1, float c2, float c3);
	void addRect(RectData rd);
	void addRect(Vec v, Vec lwh, Vec col);

	//Does nothing
	void addPlane(float x, float y, float z,
		float length, float width, float height,
		float c1, float c2, float c3);
	void addPlane(RectData rd);
	void addPlane(Vec v, Vec lwh, Vec col);

	void release();
	void clear();

	Vertex* getPVerts();
	std::vector<Vertex> getVerts();
	std::vector<int> getInds();
	int* getPInds();

private:
	std::vector<Vertex> mVertList;
	std::vector<int> mIndList;
	Vertex mVertex;
};

#endif