
#ifndef __GRAPHICSLAYER_H__
#define __GRAPHICSLAYER_H__


#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxerr8.lib")
#pragma comment(lib,"winmm.lib")

#include <D3D9.h>
#include <D3DX9.h>
#include <string>
#include <map>
#include "cRectangle.h"
#include "cScene.h"
#include "cMouse.h"
#include "cCritter.h"
#include "cSkeleton.h"

class cGraphicsLayer  
{

public:
	
	cGraphicsLayer();
	virtual ~cGraphicsLayer();

	bool Init(HWND hWnd,bool); 
	void Finalize();
	
	void LoadData();
	void UnLoadData();

	void DrawSprite(std::string &text_id, float posx, float posy, cRectangle *Rect=nullptr);

	
	// USELESS
	bool Render(int state,cMouse *Mouse,cScene *Scene,cCritter *Critter,cSkeleton *Skeleton);

	bool DrawScene(cScene *Scene);
	bool DrawUnits(cScene *Scene,cCritter *Critter,cSkeleton *Skeleton);
	bool DrawMouse(cMouse *Mouse);
	bool DrawRect(RECT rc, D3DCOLOR color);

private:

	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	LPD3DXSPRITE g_pSprite;

	std::map<std::string, LPDIRECT3DTEXTURE9>	m_texturesmap;
	LPDIRECT3DTEXTURE9 texMain,texGame;
	LPDIRECT3DTEXTURE9 texTiles,texCharacters,texMouse;
};


#endif