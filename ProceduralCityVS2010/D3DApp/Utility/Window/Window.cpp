#include "Window.h"

#include <windows.h>
#include <string>
#include <stdlib.h>
#include <tchar.h>

#include "../../Main/D3DApp.h"


D3DApp * gd3dApp = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (gd3dApp != 0)
		return gd3dApp->mWindow.msgProc(msg, wParam, lParam);

	else
		return DefWindowProc(hwnd, msg, wParam, lParam);


	/*if (msg == WM_NCCREATE)
	{
		pWindow = reinterpret_cast<Window *>(((LPCREATESTRUCT)lParam)->lpCreateParams);
		::SetWindowLongPtr(hwnd, GWL_USERDATA, reinterpret_cast<LONG>(pWindow));
		pWindow->setHandle(hwnd);
		return pWindow->msgProc(msg, wParam, lParam);
	}
	else
	{
		pWindow = reinterpret_cast<Window *>(::GetWindowLong(hwnd, GWL_USERDATA));
	}

	if (pWindow)
		pWindow->msgProc(msg, wParam, lParam);

	return DefWindowProc(hwnd, msg, wParam, lParam);*/
}

Window::Window()
{
	mbTimeReset = false;
	mhMainWnd = 0;
}

Window::~Window()
{

}

void Window::init(HINSTANCE hInstance, std::string caption, int screenX, int screenY)
{
	mMainWndCaption = caption;
	mhInstance = hInstance;
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "James Window";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass FAILED!!!!!!", 0, 0);
		PostQuitMessage(0);
	}

	RECT R = { 0, 0, screenX, screenY };
	AdjustWindowRect(&R, WS_EX_STATICEDGE, false);

	mhMainWnd = CreateWindow("James Window", mMainWndCaption.c_str(), WS_EX_STATICEDGE, 100, 100, R.right, R.bottom, 0, 0, mhInstance, 0);

	if (!mhMainWnd)
	{
		MessageBox(0, "Window is null", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);
}

LRESULT Window::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		mbTimeReset = true;
		return 0;
	
	case WM_WINDOWPOSCHANGING:
		mbTimeReset = true;
		return 0;
	case WM_DESTROY:   
		PostQuitMessage(0);
		gd3dApp->exit();
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			DestroyWindow(mhMainWnd);
		}
		return 0;

	//case WM_PAINT:
	//	return 0;
	}


	return DefWindowProc(mhMainWnd, msg, wParam, lParam);
}

bool Window::isTimeReset()
{
	return mbTimeReset;
}

void Window::setTimeReset(bool yn)
{
	mbTimeReset = yn;
}

HINSTANCE Window::getInstance()
{
	return mhInstance;
}

void Window::setInstance(HINSTANCE hInstance)
{
	mhInstance = hInstance;
}

void Window::setHandle(HWND handle)
{
	mhMainWnd = handle;
}

HWND Window::getHandle()
{
	return mhMainWnd;
}

void Window::setCaption(std::string caption)
{
	mMainWndCaption = caption;
}

std::string Window::getCaption()
{
	return mMainWndCaption;
}

bool Window::handleMessages(MSG &msg)
{
	bool flag = false;
	if (PeekMessage(&msg, mhMainWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		flag = true;
	}	
	return flag;
}