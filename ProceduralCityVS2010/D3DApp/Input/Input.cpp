#include "Input.h"

Input::Input()
{
	mKeyboardCoopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	mMouseCoopFlags = DISCL_EXCLUSIVE | DISCL_FOREGROUND;
}

Input::~Input()
{
	if (mDInput)
	{
		mDInput->Release();
		mDInput = 0;
	}

	mKeyboard->Unacquire();
	mMouse->Unacquire();

	if (mKeyboard)
	{
		mKeyboard->Release();
		mKeyboard = 0;
	}

	if (mMouse)
	{
		mMouse->Release();
		mMouse = 0;
	}
}

void Input::init(HWND hWindow, HINSTANCE hInstance)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDInput, 0);

	mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0);
	mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	mKeyboard->SetCooperativeLevel(hWindow, mKeyboardCoopFlags);
	mKeyboard->Acquire();

	mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0);
	mMouse->SetDataFormat(&c_dfDIMouse2);
	mMouse->SetCooperativeLevel(hWindow, mMouseCoopFlags);
	mMouse->Acquire();
}


void Input::poll()
{
	HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (void**)&mKeyboardState);

	if (FAILED(hr))
	{
		ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		hr = mKeyboard->Acquire();
	}

	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&mMouseState);

	if (FAILED(hr))
	{
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		hr = mMouse->Acquire();
	}
}

bool Input::keyDown(unsigned char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

bool Input::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

float Input::mouseDX()
{
	return (float)mMouseState.lX;
}

float Input::mouseDY()
{
	return (float)mMouseState.lY;
}

float Input::mouseDZ()
{
	return (float)mMouseState.lZ;
}
