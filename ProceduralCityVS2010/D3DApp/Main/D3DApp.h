#include "../Utility/Graphics/Graphics.h"
#include "../Utility/Window/Window.h"
#include "../Input/Input.h"
#include <string>
#include <windows.h>


#ifndef D3DAPP_H
#define D3DAPP_H

/*

This declares the D3DApp, which will be our inherited game class.
It will have an input object, a graphics object


*/

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY);
	virtual ~D3DApp();

	HINSTANCE getAppInst();
	Window getWnd();

	virtual bool checkDeviceCaps() { return true; }
	virtual void lostGraphics() {}
	virtual void resetGraphics() {}
	virtual void update(float dt) {}
	virtual void draw() {}
	virtual void init() {}

	void		initMainWindow();
	int			run();

	void		enableFullScreen(bool enable);
	bool		isGraphicsLost();

	Window		mWindow;

protected:
	Graphics	mGraphics;
	Input		mInput;

	
};

extern D3DApp * gd3dApp;

#endif