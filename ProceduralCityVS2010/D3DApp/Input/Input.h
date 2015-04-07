#include <dinput.h>
#include <windows.h>

#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	Input();
	~Input();

	void poll();
	void init(HWND hWindow, HINSTANCE hInstance);
	void setInstance(HINSTANCE hInstance);
	bool keyDown(unsigned char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

private:
	IDirectInput8* mDInput;

	IDirectInputDevice8* mKeyboard;
	unsigned char mKeyboardState[256];

	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState;

	DWORD mKeyboardCoopFlags;
	DWORD mMouseCoopFlags;
};

#endif