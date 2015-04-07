#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <vector>
#include <map>

#ifndef TEXTUREPILE_H
#define TEXTUREPILE_H



// a class that has a list of all texture objects
//Singleton!



class TexturePile
{
public:
	TexturePile();
	~TexturePile();

	void add(std::string type, std::string file);
	
	IDirect3DTexture9* getTexByFile(std::string file);
	IDirect3DTexture9* getTexByType(std::string type);
	
	void release();

private:
	//map of type to file
	//map of file to tex
	std::map<std::string, std::string> typetoFile;
	std::map<std::string, IDirect3DTexture9*> filetoTex;
};

#endif