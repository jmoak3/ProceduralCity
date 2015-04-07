#include "VindexPile.h"

VindexPile::VindexPile()
{

}

VindexPile::~VindexPile()
{
	release();
}

void VindexPile::init(IDirect3DDevice9* d3dDevice)
{
	mVertex.init(d3dDevice);
	mVertList.reserve(1000);
	mIndList.reserve(1000);
}

void VindexPile::addRect(float x, float y, float z,
	float length, float width, float height,
	float c1, float c2, float c3)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, z);
	D3DXVECTOR3 scale = D3DXVECTOR3(length, width, height);
	D3DXCOLOR col = D3DXCOLOR(c1, c2, c3, 1.0f);

	D3DXVECTOR3 v[24];
	v[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	v[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	v[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	v[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);

	v[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	v[5] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	v[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	v[7] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);

	v[8] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	v[9] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	v[10] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	v[11] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);

	v[12] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	v[13] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	v[14] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	v[15] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);

	v[16] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	v[17] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	v[18] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	v[19] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);

	v[20] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	v[21] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	v[22] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	v[23] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXMATRIX T, S, F;
	D3DXMatrixTranslation(&T, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	F = S*T;
	for (int i = 0; i < 24; ++i)
		D3DXVec3TransformCoord(&v[i], &v[i], &F);

	D3DXVECTOR3 n[24];
	for (int i = 0; i < 4; ++i)
		n[i] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	for (int i = 4; i < 8; ++i)
		n[i] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	for (int i = 8; i < 12; ++i)
		n[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	for (int i = 12; i < 16; ++i)
		n[i] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	for (int i = 16; i < 20; ++i)
		n[i] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	for (int i = 20; i < 24; ++i)
		n[i] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	for (int i = 0; i < 24; ++i)
	{
		mVertList.push_back(Vertex(v[i], n[i], col));
	}

	int inds = mVertList.size()-24;
	int k[36];
	k[0] = 0 + inds; k[1] = 1 + inds; k[2] = 2 + inds;
	k[3] = 0 + inds; k[4] = 2 + inds; k[5] = 3 + inds;

	k[6] = 4 + inds; k[7] = 5 + inds; k[8] = 6 + inds;
	k[9] = 4 + inds; k[10] = 6 + inds; k[11] = 7 + inds;

	k[12] = 8 + inds; k[13] = 9 + inds; k[14] = 10 + inds;
	k[15] = 8 + inds; k[16] = 10 + inds; k[17] = 11 + inds;

	k[18] = 12 + inds; k[19] = 13 + inds; k[20] = 14 + inds;
	k[21] = 12 + inds; k[22] = 14 + inds; k[23] = 15 + inds;

	k[24] = 16 + inds; k[25] = 17 + inds; k[26] = 18 + inds;
	k[27] = 16 + inds; k[28] = 18 + inds; k[29] = 19 + inds;
	
	k[30] = 20 + inds; k[31] = 21 + inds; k[32] = 22 + inds;
	k[33] = 20 + inds; k[34] = 22 + inds; k[35] = 23 + inds;

	for (int i = 0; i < 36; ++i)
		mIndList.push_back(k[i]);
}

void VindexPile::addPlane(float x, float y, float z,
	float length, float width, float height,
	float c1, float c2, float c3)
{
	addRect(x, y, z, length, width, height, c1, c2, c3);
}

void VindexPile::addRect(RectData rd)
{
	VindexPile::addRect(rd.x, rd.y, rd.z,
		rd.length, rd.width, rd.height,
		rd.c1, rd.c2, rd.c3);
}

void VindexPile::addRect(Vec v, Vec lwh, Vec col)
{
	VindexPile::addRect(v.x, v.y, v.z,
			lwh.x, lwh.y, lwh.z,
			col.x, col.y, col.z);
}

void VindexPile::addPlane(RectData rd)
{
	VindexPile::addPlane(rd.x, rd.y, rd.z,
		rd.length, rd.width, rd.height,
		rd.c1, rd.c2, rd.c3);
}

void VindexPile::addPlane(Vec v, Vec lwh, Vec col)
{
	VindexPile::addRect(v.x, v.y, v.z,
		lwh.x, lwh.y, lwh.z,
		col.x, col.y, col.z);
}

void VindexPile::release()
{
	//TODO flesh out
	mVertList.clear();
	mVertex.release();
}

void VindexPile::clear()
{
	//TODO flesh out
	mVertList.clear();
	mIndList.clear();
}

std::vector<Vertex> VindexPile::getVerts()
{
	return mVertList;
}

Vertex* VindexPile::getPVerts()
{
	return &mVertList[0];
}

int* VindexPile::getPInds()
{
	return &mIndList[0];
}


std::vector<int> VindexPile::getInds()
{
	return mIndList;
}



