#include "cCharacter.h"
#include "cGame.h"

cCharacter::cCharacter() :
	cBaseEntity()
{

}

cCharacter::cCharacter(const std::string& textureId, const cRectangle& textureRect, s32 x, s32 y, s32 z, s32 vStraight, s32 vDiagonal, f32 textureScale)
{
	Init(textureId, textureRect, x, y, z, vStraight, vDiagonal, textureScale);
}

cCharacter::~cCharacter()
{

}

void cCharacter::Init(const std::string& textureId, const cRectangle& textureRect, s32 x, s32 y, s32 z, s32 vStraight, s32 vDiagonal, f32 textureScale)
{
	SetPosition(x, y);
	SetZIndex(z);
	SetTextureID(textureId);
	SetTextureRect(textureRect);
	SetZIndex(z);
	EnableCollision();
	SetCollisionRectRelative(textureRect);
	SetTextureScale(textureScale);

	m_vStraight = vStraight;
	m_vDiagonal = vDiagonal;
}

bool cCharacter::Move(s32 xAmount, s32 yAmount)
{
	bool moveOk = false;
	m_last_orientation = m_orientation;

	if (xAmount || yAmount)
	{
		// Busco l'orientacio del moviment
		if (yAmount == 0)
		{
			if (xAmount > 0)		m_orientation = ORIENTATION_E;
			else if (xAmount < 0)	m_orientation = ORIENTATION_O;
		}
		else if (yAmount > 0)
		{
			if (xAmount > 0)		m_orientation = ORIENTATION_SE;
			else if (xAmount < 0)	m_orientation = ORIENTATION_SO;
			else				m_orientation = ORIENTATION_S;
		}
		else
		{
			if (xAmount > 0)		m_orientation = ORIENTATION_NE;
			else if (xAmount < 0)	m_orientation = ORIENTATION_NO;
			else				m_orientation = ORIENTATION_N;
		}

		

		int x, y;
		GetPosition(x, y);

		//Actualitzo el moviment segons orientacio
		switch (m_orientation)
		{
		case ORIENTATION_N:
			y -= m_vStraight;
			break;
		case ORIENTATION_NE:
			y -= m_vDiagonal;
			x += m_vDiagonal;
			break;
		case ORIENTATION_NO:
			y -= m_vDiagonal;
			x -= m_vDiagonal;
			break;
		case ORIENTATION_S:
			y += m_vStraight;
			break;
		case ORIENTATION_SE:
			y += m_vDiagonal;
			x += m_vDiagonal;
			break;
		case ORIENTATION_SO:
			y += m_vDiagonal;
			x -= m_vDiagonal;
			break;
		case ORIENTATION_E:
			x += m_vStraight;
			break;
		case ORIENTATION_O:
			x -= m_vStraight;
			break;
		}

		cRectangle destRect = GetCollisionRectAbsolute();
		destRect.x = x;
		destRect.y = y;

		cGame* game = cGame::Instance();

		if (game->globals.limits.inside(x, y))
		{
			if (game->Scene->m_map.isWalkable(destRect))
			{
				SetPosition(x, y);
				moveOk = true;
			}
		}
	}

	return moveOk;
}

bool cCharacter::PossibleMovement(s32 a_x, s32 a_y, s32& a_final_x, s32& a_final_y)
{
	bool moveOk = false;
	CharacterOrientation orientation;
	if (a_x || a_y)
	{
		// Busco l'orientacio del moviment
		if (a_y == 0)
		{
			if (a_x > 0)		orientation = ORIENTATION_E;
			else if (a_x < 0)	orientation = ORIENTATION_O;
		}
		else if (a_y > 0)
		{
			if (a_x > 0)		orientation = ORIENTATION_SE;
			else if (a_x < 0)	orientation = ORIENTATION_SO;
			else				orientation = ORIENTATION_S;
		}
		else
		{
			if (a_x > 0)		orientation = ORIENTATION_NE;
			else if (a_x < 0)	orientation = ORIENTATION_NO;
			else				orientation = ORIENTATION_N;
		}

		int x, y;
		GetPosition(x, y);

		//Actualitzo el moviment segons orientacio
		switch (orientation)
		{
		case ORIENTATION_N:
			y -= m_vStraight;
			break;
		case ORIENTATION_NE:
			y -= m_vDiagonal;
			x += m_vDiagonal;
			break;
		case ORIENTATION_NO:
			y -= m_vDiagonal;
			x -= m_vDiagonal;
			break;
		case ORIENTATION_S:
			y += m_vStraight;
			break;
		case ORIENTATION_SE:
			y += m_vDiagonal;
			x += m_vDiagonal;
			break;
		case ORIENTATION_SO:
			y += m_vDiagonal;
			x -= m_vDiagonal;
			break;
		case ORIENTATION_E:
			x += m_vStraight;
			break;
		case ORIENTATION_O:
			x -= m_vStraight;
			break;
		}

		cRectangle destRect = GetCollisionRectAbsolute();
		destRect.x = x;
		destRect.y = y;

		cGame* game = cGame::Instance();

		if (game->Scene->m_map.isWalkable(destRect))
		{
			a_final_x = x, a_final_y = y;
			moveOk = true;
		}
	}

	return moveOk;
}
