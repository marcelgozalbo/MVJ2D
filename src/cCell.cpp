#include "cCell.h"
#include <stdexcept>
#include "cGame.h"
#include "cLog.h"

cCell::cCell(unsigned int _row, unsigned int _col, const sCellInfo& _cellInfo) :
cBaseEntity("tilemap", _col * tileWidth, _row * tileHeight, 1),
	m_walkable(_cellInfo.walkable)
{
	const tFrameVec& frameVec = _cellInfo.frameVec;

	// frameVec size already checked in map
	SetTextureRect(cRectangle(frameVec[0].frameId * tileWidth, 0, tileWidth, tileHeight));
	
	// animacio
	if (frameVec.size() > 1)
	{
		std::vector<cRectangle> rectVec;
		rectVec.reserve(frameVec.size());

		for (auto& frameInfo : frameVec)
		{
			rectVec.push_back(cRectangle(frameInfo.frameId * tileWidth, 0, tileWidth, tileHeight));
		}

		SetAnimationSteps(rectVec);
		//// #todo: duracions variables d'animacio
		//// #todo: animacions per temps i no per frame
		SetAnimationFramesPerStep(_cellInfo.frameVec[0].duration * 60);
		EnableAnimation();
		PlayAnimation();
	}

	if (!m_walkable)
	{
		SetCollisionRectRelative(cRectangle(0, 0, tileWidth, tileHeight));
		EnableCollision();
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
