
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

	void DrawSprite(const std::string &text_id, int posx, int posy, int posz, const cRectangle& Rect, float scalex = 1.0, float scaley = 1.0, float scalez = 1.0, float rotx = 0.0, float roty = 0.0);
	void DrawRect(const cRectangle &Rectangle, D3DCOLOR color, int posz);
	void DrawFont(const std::string &a_text_id, const std::string& a_text, int posz, const cRectangle& a_rect, D3DCOLOR a_color = 0xFFFFFFFF, DWORD a_format = DT_LEFT);

	void GetTextureSizes(const std::string &text_id, int &h, int &w);

	void Render();

private:
	class IRender
	{
	public:
		virtual ~IRender() { }
		virtual void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev) = 0;
	};


	class RectangleRenderer : public IRender
	{
	public:
		RectangleRenderer(const cRectangle &_Rectangle, D3DCOLOR _color) :
			Rectangle(_Rectangle), color(_color){	}
		void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev)
		{
			RECT rect;
			RECT rc;
			SetRect(&rc, Rectangle.x, Rectangle.y, Rectangle.x + Rectangle.w, Rectangle.y + Rectangle.h);
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
		TextureRenderer(LPDIRECT3DTEXTURE9 _textureid, int _posx, int _posy, const cRectangle& _rect, float _scalex, float _scaley, float _scalez, float _rotx, float _roty) :
			textureid(_textureid), posx(_posx), posy(_posy), scalex(_scalex), scaley(_scaley), scalez(_scalez), rect(_rect), rotx(_rotx), roty(_roty)
		{

		}

		~TextureRenderer()	
		{

		}

		void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev)	{
			HRESULT hr;

			spr->Begin(D3DXSPRITE_ALPHABLEND);



			
			D3DXMATRIX matrixscale, matrixtranslation, matrixtransform, matrixrotationX, matrixrotationY;
			
			D3DXMatrixRotationX(&matrixrotationX, D3DXToRadian(rotx));
			D3DXMatrixRotationY(&matrixrotationY, D3DXToRadian(roty));
			D3DXMatrixTranslation(&matrixtranslation, (float)posx,(float) posy, 0.0);
			D3DXMatrixScaling(&matrixscale, scalex, scaley, scalez);

			D3DXMatrixMultiply(&matrixtransform, &matrixrotationY, &matrixrotationX);
			D3DXMatrixMultiply(&matrixtransform, &matrixtransform, &matrixscale);
			D3DXMatrixMultiply(&matrixtransform, &matrixtransform, &matrixtranslation);
			
			spr->SetTransform(&matrixtransform);
			

			RECT rc;
			SetRect(&rc, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
			//hr = spr->Draw(textureid, &rc, NULL, &D3DXVECTOR3(float(posx), float(posy), 0.0), 0xFFFFFFFF);
			hr = spr->Draw(textureid, &rc, NULL,NULL, 0xFFFFFFFF);
			spr->End();
		}
	private:

		int posx, posy;
		float scalex, scaley, scalez;
		float roty, rotx;
		LPDIRECT3DTEXTURE9 textureid;
		cRectangle rect;
	};

	class FontRenderer : public IRender
	{
	public:
		FontRenderer(LPD3DXFONT a_font, const std::string& aText, const cRectangle& a_rect, D3DCOLOR a_color = 0xFFFFFFFF, DWORD a_format = DT_LEFT) :
			_font(a_font), _text(aText), _rect(a_rect), _color(a_color), _format(a_format)
		{

		}

		~FontRenderer()
		{

		}

		void Render(LPD3DXSPRITE spr, LPDIRECT3DDEVICE9 dev) override
		{
			HRESULT hr;
			spr->Begin(D3DXSPRITE_ALPHABLEND);

			D3DXMATRIX matrixscale, matrixtranslation, matrixtransform;

			
			D3DXMatrixTranslation(&matrixtranslation, (float)_rect.x, (float)_rect.y, 0.0);
			D3DXMatrixScaling(&matrixscale, 1.0,1.0,1.0);
			D3DXMatrixMultiply(&matrixtransform, &matrixscale, &matrixtranslation);

			spr->SetTransform(&matrixtransform);
			
			//RECT rc;
			//SetRect(&rc, 0, 0, _rect.w, _rect.h);
			hr = _font->DrawText(spr, _text.c_str(), -1, NULL, _format, _color);
			spr->End();
		}
	private:

		LPD3DXFONT _font;
		const std::string _text;
		cRectangle _rect;
		D3DCOLOR _color;
		DWORD _format;

	};

	typedef std::vector<IRender *> tZOrderVec;
	typedef std::map<int, tZOrderVec> tRenderFrameInfo;

	// Variables

	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	LPD3DXSPRITE g_pSprite;

	std::map<std::string, LPDIRECT3DTEXTURE9>	m_texturesmap;
	std::map<std::string, LPD3DXFONT>			m_fontsmap;

	// Z, renderinfo
	tRenderFrameInfo	m_renderframeinfo;

};


#endif
