
#include "GfxStats.h"
#include <stdio.h>

GfxStats::GfxStats()
: mFont(0), mFPS(0.0f), mMilliSecPerFrame(0.0f)
{
	
}

GfxStats::~GfxStats()
{
	if (mFont)
	{
		mFont->Release();
		mFont = 0;
	}
}

void GfxStats::init(IDirect3DDevice9* d3dDevice)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height          = 18;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    strcpy_s(fontDesc.FaceName, ("Times New Roman"));

	D3DXCreateFontIndirect(d3dDevice, &fontDesc, &mFont);
}

void GfxStats::onLostDevice()
{
	mFont->OnLostDevice();
}

void GfxStats::onResetDevice()
{
	mFont->OnResetDevice();
}
void GfxStats::update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment the frame count.
	numFrames += 1.0f;

	// Accumulate how much time has passed.
	timeElapsed += dt;

	// Has one second passed?--we compute the frame statistics once 
	// per second.  Note that the time between frames can vary so 
	// these stats are averages over a second.
	if( timeElapsed >= 1.0f )
	{
		// Frames Per Second = numFrames / timeElapsed,
		// but timeElapsed approx. equals 1.0, so 
		// frames per second = numFrames.

		mFPS = numFrames;

		// Average time, in miliseconds, it took to render a single frame.
		mMilliSecPerFrame = 1000.0f / mFPS;

		// Reset time counter and frame count to prepare for computing
		// the average stats over the next second.
		timeElapsed = 0.0f;
		numFrames   = 0.0f;
	}
}

void GfxStats::display()
{
	// Make static so memory is not allocated every frame.
	static char buffer[256];

	sprintf_s(buffer, "Frames Per Second = %.2f\n"
		"Milliseconds Per Frame = %.4f\n", 
		mFPS, mMilliSecPerFrame);

	RECT R = {5, 5, 0, 0};
	mFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0));
}