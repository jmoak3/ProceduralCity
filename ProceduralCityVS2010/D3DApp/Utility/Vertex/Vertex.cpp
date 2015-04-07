#include "Vertex.h"

IDirect3DVertexDeclaration9* Vertex::Decl = 0;

void Vertex::init(IDirect3DDevice9* d3dDevice)
{
	D3DVERTEXELEMENT9 VertexElements[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	d3dDevice->CreateVertexDeclaration(VertexElements, &Vertex::Decl);
}

void Vertex::release()
{
	if (Vertex::Decl)
	{
		Vertex::Decl->Release();
		Vertex::Decl = 0;
	}
}
