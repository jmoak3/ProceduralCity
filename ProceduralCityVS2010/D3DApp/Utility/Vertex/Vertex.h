#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#ifndef VERTEX_H
#define	VERTEX_H

class Vertex
{
public:
	Vertex() :pos(0.0f, 0.0f, 0.0f), 
				normal(0.0f, 0.0f, 0.0f),
				col(0.0f, 0.0f, 0.0f, 1.0f) {}
	Vertex(float x, float y, float z,
				float nx, float ny, float nz,
				D3DXCOLOR c) 
				:pos(x, y, z), normal(nx, ny, nz), col(c) {}
	Vertex(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXCOLOR& c)
				:pos(v), normal(n), col(c) {}
	~Vertex() {}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXCOLOR    col;
	static IDirect3DVertexDeclaration9* Decl;

	static void init(IDirect3DDevice9* d3dDevice);

	static void release();
};


#endif