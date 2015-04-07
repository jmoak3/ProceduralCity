#include <windows.h>
#include <string>
#include <stdlib.h>
#include <tchar.h>

#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
	Window();
	~Window();
	//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	LRESULT CALLBACK msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void		init(HINSTANCE hInstance, std::string caption, int screenX, int screenY);

	bool		handleMessages(MSG &msg);

	void	    setInstance(HINSTANCE instance);
	HINSTANCE   getInstance();

	void	    setHandle(HWND handle);
	HWND	    getHandle();

	void	    setCaption(std::string caption);
	std::string getCaption();

	bool		isTimeReset();
	void		setTimeReset(bool yn);
	
private:
	HINSTANCE   mhInstance;
	HWND	    mhMainWnd;

	bool		mbTimeReset;
	std::string mMainWndCaption;
};
#endif