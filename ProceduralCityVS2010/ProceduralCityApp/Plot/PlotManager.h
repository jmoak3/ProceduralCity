#include "../../D3DApp/Utility/Graphics/Graphics.h"
#include <vector>

#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

class PlotManager
{
public:
	PlotManager() {}
	~PlotManager() {}

	void init();

	void update(float dt);
	void draw(Graphics* g);

	void addPlot(float x, float z, float x2, float z2);

private:
	
	//list of turns
	//roadlist
};

#endif