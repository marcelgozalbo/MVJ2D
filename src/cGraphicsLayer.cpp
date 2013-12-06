#include "cGraphicsLayer.h"
#include "cGame.h"
#include "cLog.h"
#include <stdio.h>

cGraphicsLayer::cGraphicsLayer()
{
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
	g_pSprite = NULL;
}

cGraphicsLayer::~cGraphicsLayer(){}

bool cGraphicsLayer::Init(HWND hWnd, bool exclusive)
{
	cLog *Log = cLog::Instance();
	HRESULT hr;
	D3DVIEWPORT9 viewPort = { 0, 0, SCREEN_RES_X, SCREEN_RES_Y, 0.0f, 1.0f };
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		Log->Msg("Error creating Direct3D object");
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !exclusive;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //Efficient page flipping
	d3dpp.BackBufferWidth = SCREEN_RES_X;
	d3dpp.BackBufferHeight = SCREEN_RES_Y;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd, // exclusive ? hWnd : NULL,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice);
	if (FAILED(hr))
	{
		Log->Error(hr, "Creating Direct3D device");
		return false;
	}
	hr = g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	if (FAILED(hr))
	{
		Log->Error(hr, "Setting render state");
		return false;
	}
	hr = g_pD3DDevice->SetViewport(&viewPort);
	if (FAILED(hr))
	{
		Log->Error(hr, "Setting viewport");
		return false;
	}
	if (FAILED(hr))
	{
		Log->Error(hr, "Creating Direct3D font");
		return false;
	}
	return true;
}

void cGraphicsLayer::Finalize()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

void cGraphicsLayer::LoadData()
{
	D3DXCreateSprite( g_pD3DDevice, &g_pSprite ); 

	LPDIRECT3DTEXTURE9 buffer = nullptr;
	
	//Main background
	D3DXCreateTextureFromFileEx(g_pD3DDevice, "../media/main.jpg", 0, 0, 1, 0, D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
								NULL, NULL, NULL, &buffer);
	m_texturesmap["main"] = buffer;

	//GUI game
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"../media/game.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								NULL, NULL, NULL, &buffer);
	m_texturesmap["GUI"] = buffer;

	//Tiles
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"../media/tiles.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff, NULL, NULL, &buffer);
	m_texturesmap["tilemap"] = buffer;

	//Characters
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"../media/characters.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff, NULL, NULL, &buffer);
	m_texturesmap["characters"] = buffer;

	//Player
	D3DXCreateTextureFromFileEx(g_pD3DDevice, "../media/Player.png", 0, 0, 1, 0, D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
								0x00ff00ff, NULL, NULL, &buffer);
	m_texturesmap["player"] = buffer;

	//Mouse pointers
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"../media/mouse.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff, NULL, NULL, &buffer);
	m_texturesmap["mouse"] = buffer;

	//Green arrow
	D3DXCreateTextureFromFileEx(g_pD3DDevice, "../media/green_arrow.png", 0, 0, 1, 0, D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
								0x00ff00ff, NULL, NULL, &buffer);
	m_texturesmap["green_arrow"] = buffer;
}

void cGraphicsLayer::GetTextureSizes(const std::string &text_id, int &h, int &w)
{
	auto text_it = m_texturesmap.find(text_id);

	if (text_it == m_texturesmap.end())
	{
		cLog *Log = cLog::Instance();
		Log->Msg(std::string("GetTextureInfo Texture id: ") + text_id + std::string(" Not Found!"));
		h = 0;
		w = 0;
		return;
	}

	D3DSURFACE_DESC desc;
	text_it->second->GetLevelDesc(0, &desc);

	h = desc.Height;
	w = desc.Width;

}

void cGraphicsLayer::UnLoadData()
{
	for(auto &p: m_texturesmap)
		p.second->Release();


	if(g_pSprite)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}
}

void cGraphicsLayer::Render()
{
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET , 0xFF000000, 1.0f, 0);
	g_pD3DDevice->BeginScene();

	//Start Rendering by Z order
	for (auto rit = m_renderframeinfo.begin(); rit != m_renderframeinfo.end(); ++rit)
		for (auto &it_Zlevel : rit->second) 	// RENDER Z entire Z-LEVEL
			it_Zlevel->Render(g_pSprite, g_pD3DDevice);
	

	//Clean the entire map for the next frame
	for (auto &it_renderinfo : m_renderframeinfo)
		for (auto &it_Zlevel : it_renderinfo.second)
			delete it_Zlevel;

	m_renderframeinfo.clear();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
	
}

void cGraphicsLayer::DrawSprite(const std::string &text_id, int posx, int posy, int posz, cRectangle *Rect, float scalex, float scaley, float scalez)
{
	auto text_it = m_texturesmap.find(text_id);

	if (text_it == m_texturesmap.end())
	{
		cLog *Log = cLog::Instance();
		Log->Msg(std::string("DRAWSPRITE Texture id: ") + text_id + std::string(" Not Found!"));
		return;
	}

	TextureRenderer *ptex = new TextureRenderer(text_it->second, posx, posy, Rect, scalex, scaley,scalez);
	auto rendit = m_renderframeinfo.find(posz);
	if (rendit == m_renderframeinfo.end())
	{
		std::vector<IRender *> vec;
		vec.push_back(ptex);
		m_renderframeinfo.insert(std::pair < int, std::vector<IRender *>  >(posz, vec));
	}
	else
	{
		rendit->second.push_back(ptex);
	}
}


void cGraphicsLayer::DrawRect(const cRectangle &Rectangle, D3DCOLOR color, int posz)
{
	RectangleRenderer *ptex = new RectangleRenderer(Rectangle,color);
	auto rendit = m_renderframeinfo.find(posz);
	if (rendit == m_renderframeinfo.end())
	{
		std::vector<IRender *> vec;
		vec.push_back(ptex);
		m_renderframeinfo.insert(std::pair < int, std::vector<IRender *>  >(posz, vec));
	}
	else
	{
		rendit->second.push_back(ptex);
	}
	
}



