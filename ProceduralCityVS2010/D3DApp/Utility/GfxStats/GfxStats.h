#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <tchar.h>

#ifndef GFX_STATS_H
#define GFX_STATS_H

class GfxStats
{
public:
	GfxStats();
	~GfxStats();

	void init(IDirect3DDevice9* d3dDevice);

	void onLostDevice();
	void onResetDevice();

	void update(float dt);
	void display();

private:
	// Prevent copying
	GfxStats(const GfxStats& rhs);
	GfxStats& operator=(const GfxStats& rhs);
	
private:
	ID3DXFont* mFont;
	float mFPS;
	float mMilliSecPerFrame;
};
#endif
