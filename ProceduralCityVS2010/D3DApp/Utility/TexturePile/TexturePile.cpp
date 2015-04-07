#include "TexturePile.h"

TexturePile::TexturePile()
{

}

TexturePile::~TexturePile()
{
	release();
}

void TexturePile::add(std::string type, std::string file)
{
	typetoFile[type] = file;
}

IDirect3DTexture9* TexturePile::getTexByFile(std::string file)
{
	return filetoTex[file];
}

IDirect3DTexture9* TexturePile::getTexByType(std::string type)
{
	return filetoTex[typetoFile[type]];
}

void TexturePile::release()
{
	//TODO flesh out
	// (!typetoFile.empty())
	//	typetoFile.clear();
	//if (!filetoTex.empty())
	//	filetoTex.clear();
}
