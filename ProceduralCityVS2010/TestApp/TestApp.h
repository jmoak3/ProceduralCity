
#include <Windows.h>
#include "../D3DApp/Main/D3DApp.h"

#ifndef TESTAPP_H
#define	TESTAPP_H


class TestApp : public D3DApp
{
public:
	TestApp(HINSTANCE hInstance, std::string winCaption, int screenX, int screenY);
	~TestApp();


	bool checkDeviceCaps();
	void lostGraphics();
	void resetGraphics();
	void update(float dt);
	void draw();

	void init();

private:

};

#endif