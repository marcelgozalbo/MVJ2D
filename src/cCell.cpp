#include "cCell.h"
#include "cGame.h"
#include "cLog.h"

cCell::cCell(int _row, int _col, int _cellId, bool _walkable) :
	cBaseEntity("tilemap", _row * tileWidth, _col * tileHeight, 1),
	m_walkable(_walkable)
{
	cRectangle rec(_cellId * tileWidth, 0, tileWidth, tileHeight);
	SetTextureRect(rec);

	if (!m_walkable)
	{
		EnableCollision();
		SetCollisionRectRelative(rec);
	}

	cLog::Instance()->Msg("Creating cell pos:%u,%u ref:%u,%u", _row * tileWidth, _col * tileHeight, _cellId * tileWidth, 0);
}

cCell::~cCell()
{

}

bool cCell::isWalkable() const
{
	return m_walkable;
}

void cCell::render()
{
	cBaseEntity::Render();
}

void cCell::update()
{
	cBaseEntity::Update();
}
