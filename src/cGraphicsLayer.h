
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
#include <vector>
#include "cRectangle.h"




class cGraphicsLayer  
{

public:
	
	cGraphicsLayer();
	virtual ~cGraphicsLayer();

	bool Init(HWND hWnd,bool); 
	void Finalize();
	
	void LoadData();
	void UnLoadData();

	void DrawSprite(std::string &text_id, float posx, float posy, int posz, cRectangle *Rect = nullptr);
	void DrawRect(cRectangle &Rectangle, D3DCOLOR color, int posz);

	void GetTextureSizes(std::string &text_id, int &h, int &w);

	void Render();
private:
	class IRender
	{
	public:
		virtual void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev) = 0;
	};


	class RectangleRenderer : public IRender
	{
	public:
		RectangleRenderer(cRectangle &_Rectangle, D3DCOLOR _color) :
			Rectangle(_Rectangle), color(_color){	}
		void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev)
		{
			RECT rect;
			RECT rc;
			SetRect(&rc, Rectangle.x, Rectangle.y, Rectangle.w, Rectangle.h);
			int xo, yo, xf, yf;

			if ((rc.left == rc.right) && (rc.top == rc.bottom)) return;

			if (rc.left < rc.right)
			{
				xo = rc.left;	xf = rc.right;
			}
			else
			{
				xo = rc.right;	xf = rc.left;
			}
			if (rc.top < rc.bottom)
			{
				yo = rc.top;	yf = rc.bottom;
			}
			else
			{
				yo = rc.bottom;	yf = rc.top;
			}

			//Top
			SetRect(&rect, xo, yo, xf + 1, yo + 1);
			dev->Clear(1, (D3DRECT *)&rect, D3DCLEAR_TARGET, color, 1.0f, 0);
			//Bottom
			SetRect(&rect, xo, yf, xf, yf + 1);
			dev->Clear(1, (D3DRECT *)&rect, D3DCLEAR_TARGET, color, 1.0f, 0);
			//Left
			SetRect(&rect, xo, yo, xo + 1, yf + 1);
			dev->Clear(1, (D3DRECT *)&rect, D3DCLEAR_TARGET, color, 1.0f, 0);
			//Right
			SetRect(&rect, xf, yo, xf + 1, yf + 1);
			dev->Clear(1, (D3DRECT *)&rect, D3DCLEAR_TARGET, color, 1.0f, 0);
		
		}
	private:

		cRectangle Rectangle;
		D3DCOLOR color;
	};

	class TextureRenderer : public IRender
	{
	public:
		TextureRenderer(LPDIRECT3DTEXTURE9 _textureid, float _posx, float _posy, cRectangle *_rect) :
			textureid(_textureid), posx(_posx), posy(_posy), rect(nullptr){
			if (_rect != nullptr)	rect = new cRectangle(*_rect);
		}
		~TextureRenderer()	{
			if (rect == nullptr)
			{
				delete rect;
				rect = nullptr;
			}
		}

		void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev)	{
			HRESULT hr;

			spr->Begin(D3DXSPRITE_ALPHABLEND);
			if (rect == nullptr)
			{
				hr = spr->Draw(textureid, NULL, NULL, &D3DXVECTOR3(float(posx), float(posy), 0.0), 0xFFFFFFFF);
			}
			else
			{
				RECT rc;
				SetRect(&rc, rect->x, rect->y, rect->w, rect->h);
				hr = spr->Draw(textureid, &rc, NULL, &D3DXVECTOR3(float(posx), float(posy), 0.0), 0xFFFFFFFF);
			}

			spr->End();
		}
	private:

		float posx, posy;
		LPDIRECT3DTEXTURE9 textureid;
		cRectangle  *rect;
	};


	// Variables

	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	LPD3DXSPRITE g_pSprite;

	std::map<std::string, LPDIRECT3DTEXTURE9>	m_texturesmap;

	// Z, renderinfo
	std::map<int, std::vector<IRender *> >	m_renderframeinfo;

};


#endif