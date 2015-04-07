#include "ProceduralCityApp/ProceduralCityApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ProceduralCityApp app(hInstance, "ProceduralCityApp", 800, 600);
	gd3dApp = &app;
	gd3dApp->init();

	return gd3dApp->run();
}
