#ifndef MPV2D_CFONT_H_
#define MPV2D_CFONT_H_

#include <string>
#include "types.h"
#include "cRectangle.h"

class cFont
{
public:
	enum eAlignment
	{
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT,
	};

	cFont();
	cFont(const std::string& textureId, const std::string& text, u32 z, const cRectangle& rectangle, u32 color = 0xFF000000, eAlignment alignment = ALIGN_LEFT);
	~cFont();

	void setTextureId(const std::string& textureId);
	void setText(const std::string& text);
	void setZIndex(u32 z);
	void setRectangle(const cRectangle& rectangle);
	void setColor(u32 color);
	void setAlignment(eAlignment alignment);

	void render();

private:
	std::string m_textureId;
	std::string m_text;
	u32 m_z;
	cRectangle m_rectangle;
	u32 m_color;
	u32 m_alignment; // acoplat a DIRECT3D, hauriem de crear una classe filla
};

#endif
