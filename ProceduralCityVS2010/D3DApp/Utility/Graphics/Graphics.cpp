#include "Graphics.h"

#include <tchar.h>


Graphics::Graphics()
{
	ZeroMemory(&mGPP, sizeof(mGPP));
	md3dObject = 0;
	md3dDevice = 0;
	mStart = true;
}

Graphics::~Graphics()
{
	if (md3dObject)
	{
		md3dObject->Release();
		md3dObject = 0;
	}

	if (md3dDevice)
	{
		md3dDevice->Release();
		md3dDevice = 0;
	}

	if (mVB)
	{
		mVB->Release();
		mVB = 0;
	}

	if (mIB)
	{
		mIB->Release();
		mIB = 0;
	}

	mVinds.release();
	mTexs.release();

	delete mGStats;
	delete mCamera;
}

void Graphics::init(HWND hWindow, int screenX, int screenY)
{
	md3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!md3dObject)
	{
		MessageBox(0, "Direct3DCreate9 Failed", 0, 0);
		PostQuitMessage(0);
	}

	D3DDISPLAYMODE mode;
	md3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, mode.Format, mode.Format, true);
	md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false);

	D3DCAPS9 caps;
	md3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	mGPP.BackBufferWidth = screenX;
	mGPP.BackBufferHeight = screenY;
	mGPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	mGPP.BackBufferCount = 1;
	mGPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	mGPP.MultiSampleQuality = 0;
	mGPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	mGPP.hDeviceWindow = hWindow;
	mGPP.Windowed = true;
	mGPP.EnableAutoDepthStencil = true;
	mGPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	mGPP.Flags = 0;
	mGPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	mGPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	md3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &mGPP, &md3dDevice);

	mGStats = new GfxStats();
	mCamera = new Camera();

	mGStats->init(md3dDevice);
	mCamera->init();

	mLightVecW    = D3DXVECTOR3(-0.5, 0.75f, -2.0f);
	D3DXVec3Normalize(&mLightVecW, &mLightVecW);
	mDiffuseLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mAmbientLight = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mSpecularMtrl  = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mSpecularLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mSpecularPower = 8.0f;

	D3DXMatrixIdentity(&mWorld);

	buildFX();

	resetDevice();

	mVinds.init(md3dDevice);
}

bool Graphics::isLost()
{
	HRESULT hr = md3dDevice->TestCooperativeLevel();

	// If the device is lost and cannot be reset yet then
	// sleep for a bit and we'll try again on the next 
	// message loop cycle.
	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	// Driver error, exit.
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, "Internal Driver Error...Exiting", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	// The device is lost but we can reset and restore it.
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		lostDevice();
		md3dDevice->Reset(&mGPP);
		resetDevice();
		return false;
	}
	else
		return false;
}

void Graphics::lostDevice()
{
	//Call object->onLostDevice() for all objects in our graphics (fonts, fx shaders, etc)
	//for each Directx Handle object call reset
	mFX->OnLostDevice();
	mGStats->onLostDevice();
	//mhWorld->
}

void Graphics::resetDevice()
{
	//for each Directx Handle object call reset
	mFX->OnResetDevice();
	mGStats->onResetDevice();
	buildProjMtx();
}

void Graphics::addTexture(std::string type, int ID, std::string file)
{
	//Add object to objectlis
	//add file to texture
	//Type -> texture how to link
	mTexs.add(type, file);
	objectList.push_back(ID);
	idTypeMap[ID] = type;
}

void Graphics::addRect(Vec v1, Vec v2, Vec col)
{
	addRect(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, col.x, col.y, col.z);
}

void Graphics::addRect(RectData rd)
{
	addRect(rd.x, rd.y, rd.z, rd.length, rd.width, rd.height, rd.c1, rd.c2, rd.c3);
}

void Graphics::addRect(float a, float b, float c, float l, float w, float h, float c11, float c22, float c33)
{
	mVinds.addRect(a, b, c, l, w, h, c11, c22, c33);
}

void Graphics::updateBuffers()
{
	if (!mStart)
	{
		mVB->Release();
		mIB->Release();
	}
	mStart = false;

	md3dDevice->CreateVertexBuffer(mVinds.getVerts().size() * sizeof(Vertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mVB, 0);
	Vertex * v = 0;
	mVB->Lock(0, 0, (void**)&v, 0);

	const std::vector<Vertex> vList = mVinds.getVerts();

	for (int i = 0; i < vList.size(); ++i)
	{
		v[i] = vList[i];
	}

	mVB->Unlock();

	md3dDevice->CreateIndexBuffer(mVinds.getInds().size() * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIB, 0);

	WORD* ind = 0;
	mIB->Lock(0, 0, (void**)&ind, 0);

	const std::vector<int> iList = mVinds.getInds();

	for (int i = 0; i< iList.size(); ++i)
	{
		ind[i] = iList[i];
	}

	mIB->Unlock();
}

void Graphics::draw()
{
	//If no tex
	//Go through vertex lists and add to buffer
	//go through index list and add to buffer

	updateBuffers();

	md3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000ffff, 1.0f, 0);

	md3dDevice->BeginScene();

	md3dDevice->SetVertexDeclaration(Vertex::Decl);
	md3dDevice->SetStreamSource(0, mVB, 0, sizeof(Vertex));
	md3dDevice->SetIndices(mIB);
	
	
	mFX->SetTechnique(mhTech);

	mFX->SetMatrix(mhWVP, &(mCamera->viewProj()));
	D3DXMATRIX worldInverseTranspose;
	D3DXMatrixInverse(&worldInverseTranspose, 0, &mWorld);
	D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);
	mFX->SetValue(mhEyePos, &(mCamera->pos()), sizeof(D3DXVECTOR3));
	mFX->SetMatrix(mhWorldInverseTranspose, &worldInverseTranspose);
	mFX->SetValue(mhLightVecW, &mLightVecW, sizeof(D3DXVECTOR3));
	mFX->SetValue(mhDiffuseLight, &mDiffuseLight, sizeof(D3DXCOLOR));
	mFX->SetValue(mhAmbientLight, &mAmbientLight, sizeof(D3DXCOLOR));
	mFX->SetValue(mhSpecularLight, &mSpecularLight, sizeof(D3DXCOLOR));
	mFX->SetValue(mhSpecularMtrl, &mSpecularMtrl, sizeof(D3DXCOLOR));
	mFX->SetFloat(mhSpecularPower, mSpecularPower);
	mFX->SetMatrix(mhWorld, &mWorld);

	// Begin passes.
	int num = mVinds.getInds().size();
	num = num/36;
	UINT numPasses = 0;
	mFX->Begin(&numPasses, 0);
	for (UINT i = 0; i < numPasses; ++i)
	{
		mFX->BeginPass(i);
		md3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8*num, 0, 12*num);
		mFX->EndPass();
	}
	mFX->End();

	mGStats->display();

	md3dDevice->EndScene();

	// Present the backbuffer.
	md3dDevice->Present(0, 0, 0, 0);

	mVinds.clear();
}

void Graphics::buildProjMtx()
{
	float w = (float)mGPP.BackBufferWidth;
	float h = (float)mGPP.BackBufferHeight;
	mCamera->setLens(D3DX_PI * 0.25f, w / h, 1.0f, 100000.0f);
}

void Graphics::buildFX()
{
	ID3DXBuffer* errors = 0;
	if (D3DXCreateEffectFromFile(md3dDevice, "Shader.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mFX, &errors))
	if (!errors)
	{
		MessageBox(0, "Shader.fx not found!", 0, 0);
		PostQuitMessage(0);
	}

	if (errors)
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	mhTech = mFX->GetTechniqueByName("ShaderTech");
	mhWVP                   = mFX->GetParameterByName(0, "gWVP");
	mhWorldInverseTranspose = mFX->GetParameterByName(0, "gWorldInverseTranspose");
	mhLightVecW             = mFX->GetParameterByName(0, "gLightVecW");
	mhDiffuseLight          = mFX->GetParameterByName(0, "gDiffuseLight");
	mhAmbientLight          = mFX->GetParameterByName(0, "gAmbientLight");
	mhSpecularMtrl          = mFX->GetParameterByName(0, "gSpecularMtrl");
	mhSpecularLight         = mFX->GetParameterByName(0, "gSpecularLight");
	mhSpecularPower         = mFX->GetParameterByName(0, "gSpecularPower");
	mhEyePos                = mFX->GetParameterByName(0, "gEyePosW");
	mhWorld                 = mFX->GetParameterByName(0, "gWorld");
}

void Graphics::enableFullScreen(bool enable)
{

}

void Graphics::updateStats(float dt)
{
	mGStats->update(dt);
}

void Graphics::updateCamera(float dt, Input* input)
{
	mCamera->update(dt, input);
}