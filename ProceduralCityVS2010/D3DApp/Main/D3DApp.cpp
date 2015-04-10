#include "D3DApp.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

D3DApp::D3DApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY)
{
	//mWindow.setInstance(hInstance);
	//mInput.setInstance(mWindow.getInstance());
	bShouldEnd = false;
	mWindow.init(hInstance, winCaption, screenX, screenY); //!! TODO Remove public mhMainWnd, reference as variables in .init funcs
	mGraphics.init(mWindow.getHandle(), screenX, screenY);
	mInput.init(mWindow.getHandle(), hInstance);
}

D3DApp::~D3DApp()
{
	//mGraphics.~Graphics();
}

int D3DApp::run()
{
	MSG  msg;
	msg.message = WM_NULL;
	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;
	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);
	while (msg.message != WM_QUIT && !bShouldEnd)
	{
		if (!mWindow.handleMessages(msg))
		{
			if (mWindow.isTimeReset())
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);
				mWindow.setTimeReset(false);
			}
			if (!isGraphicsLost())
			{
				static float frameLimit = 0.0f;
				__int64 currTimeStamp = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
				float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;

				if (dt > 1.0f) dt = 0.0f;
				frameLimit += dt;
				if (frameLimit > 0.002500f) // 0.0167 -> 60
				{
					update(frameLimit);
					draw();
					frameLimit = 0.0f;
				}
				else if (frameLimit < 0.000200f)
					Sleep(1);
				prevTimeStamp = currTimeStamp;
			}
		}
	}
	return (int)msg.wParam;
}

bool D3DApp::isGraphicsLost()
{
	return mGraphics.isLost();
}

HINSTANCE D3DApp::getAppInst()
{
	return mWindow.getInstance();
}

Window D3DApp::getWnd()
{
	return mWindow;
}

void D3DApp::enableFullScreen(bool enable)
{
	mGraphics.enableFullScreen(enable);
}

void D3DApp::exit()
{
	bShouldEnd = true;
}