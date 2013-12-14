#include "cFont.h"
#include "cGame.h"

cFont::cFont() :
	m_z(100),
	m_color(0xFF000000)
{

}

cFont::cFont(const std::string& textureId, const std::string& text, u32 z, const cRectangle& rectangle, u32 color, eAlignment alignment)
{
	setTextureId(textureId);
	setText(text);
	setZIndex(z);
	setRectangle(rectangle);
	setColor(color);
	setAlignment(alignment);
}

cFont::~cFont()
{

}

void cFont::setTextureId(const std::string& textureId)
{
	m_textureId = textureId;
}

void cFont::setText(const std::string& text)
{
	m_text = text;
}

void cFont::setZIndex(u32 z)
{
	m_z = z;
}

void cFont::setRectangle(const cRectangle& rectangle)
{
	m_rectangle = rectangle;
}

void cFont::setColor(u32 color)
{
	m_color = color;
}

void cFont::setAlignment(eAlignment alignment)
{
	switch (alignment)
	{
	case ALIGN_CENTER:
		m_alignment = DT_CENTER;
		break;

	case ALIGN_RIGHT:
		m_alignment = DT_RIGHT;
		break;

	case ALIGN_LEFT:
	default:
		m_alignment = DT_LEFT;
		break;
	}
}

void cFont::render()
{
	cGame::Instance()->Graphics->DrawFont(m_textureId, m_text, m_z, m_rectangle, m_color, m_alignment);
}
