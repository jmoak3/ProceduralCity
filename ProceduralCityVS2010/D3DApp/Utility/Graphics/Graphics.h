
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <map>
#include <vector>

#include "../TexturePile/TexturePile.h"
#include "../VindexPile/VindexPile.h"
#include "../Vertex/Vertex.h"
#include "../Vec/Vec.h"
#include "../GfxStats/GfxStats.h"
#include "../../Input/Input.h"
#include "../Camera/Camera.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H


class Graphics
{
public:
	Graphics();
	~Graphics();
	void init(HWND hWindow, int screenX, int screenY);
	void enableFullScreen(bool enable);

	//need basetype with id and get id
	void addTexture(std::string type, int ID, std::string file);

	//take in object with type and id
	//Store same type objects in same buffer
	//Make list of type type - how to make?
	//void addVertex();

	void addRect(Vec v1, Vec lwh, Vec col);
	void addRect(float a, float b, float c, float l, float w, float h, float c11, float c22, float c33);
	void addRect(RectData rd);

	bool isLost();
	void resetDevice();
	void lostDevice();

	void updateBuffers();
	void buildProjMtx();
	void buildFX();

	void draw();
	
	void updateCamera(float dt, Input* input);
	void updateStats(float dt);
	
private:
	D3DPRESENT_PARAMETERS mGPP;

	IDirect3D9*           md3dObject;
	IDirect3DDevice9*	  md3dDevice;

	//ID and type not currently used
	std::vector<int> objectList;
	std::map<int, std::string> idTypeMap;

	TexturePile mTexs;
	VindexPile mVinds;

	Camera * mCamera;
	GfxStats* mGStats;

	IDirect3DVertexBuffer9 * mVB;
	IDirect3DIndexBuffer9 *  mIB;
	ID3DXEffect* mFX;
	D3DXHANDLE   mhTech;
	D3DXHANDLE   mhWVP;
	D3DXHANDLE   mhWorldInverseTranspose;
	D3DXHANDLE   mhLightVecW;
	D3DXHANDLE   mhDiffuseMtrl;
	D3DXHANDLE   mhDiffuseLight;
	D3DXHANDLE   mhAmbientMtrl;
	D3DXHANDLE   mhAmbientLight;
	D3DXHANDLE   mhSpecularMtrl;
	D3DXHANDLE   mhSpecularLight;
	D3DXHANDLE   mhSpecularPower;
	D3DXHANDLE   mhEyePos;
	D3DXHANDLE   mhWorld;

	D3DXVECTOR3 mLightVecW;
	D3DXCOLOR   mDiffuseMtrl;
	D3DXCOLOR   mDiffuseLight;
	D3DXCOLOR   mAmbientMtrl;
	D3DXCOLOR   mAmbientLight;
	D3DXCOLOR   mSpecularMtrl;
	D3DXCOLOR   mSpecularLight;
	float mSpecularPower;

	D3DXMATRIX mWorld;
	bool mStart;
};


#endif