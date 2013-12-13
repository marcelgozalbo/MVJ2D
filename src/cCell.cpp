#include "cCell.h"
#include <stdexcept>
#include "cGame.h"
#include "cLog.h"

cCell::cCell(unsigned int _row, unsigned int _col, const sCellInfo& _cellInfo) :
	cBaseEntity(_cellInfo.tileSet, _col * tileWidth, _row * tileHeight, _cellInfo.z),
	m_walkable(_cellInfo.walkable)
{
	const tFrameVec& frameVec = _cellInfo.frameVec;
	const sFrameInfo& finfo = frameVec[0];

	// frameVec size already checked in map
	SetTextureRect(cRectangle(frameVec[0].framePosX * tileWidth, frameVec[0].framePosY * tileHeight, tileWidth, tileHeight));
	
	// animacio
	if (frameVec.size() > 1)
	{
		std::vector<cRectangle> rectVec;
		rectVec.reserve(frameVec.size());

		for (auto& frameInfo : frameVec)
		{
			rectVec.push_back(cRectangle(frameInfo.framePosX * tileWidth, frameInfo.framePosY * tileHeight, tileWidth, tileHeight));
		}

		SetAnimationSteps(rectVec);
		SetAnimationFramesPerStep(_cellInfo.duration * 10);
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
