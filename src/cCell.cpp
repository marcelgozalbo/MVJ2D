#include "cCell.h"
#include "cGame.h"

cCell::cCell(int _row, int _col, int _cellId, bool _walkable) :
	cBaseEntity("tilemap", _row * tileWidth, _col * tileHeight, 1),
	m_walkable(_walkable)
{
	cRectangle rec(_cellId * tileWidth, _cellId* tileHeight, tileWidth, tileHeight);
	SetTextureRect(rec);

	if (!m_walkable)
	{
		EnableCollision();
		SetCollisionRectRelative(rec);
	}
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
