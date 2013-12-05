#include "cPlayer.h"

#include "cGame.h"
cPlayer::cPlayer():
cBaseEntity("player",0, 0, 0)
{
	cRectangle rec(0, 0, 16,24);
	SetTextureRect(rec);
	EnableCollision();
	SetCollisionRectRelative(rec);
	SetTextureScale(4.0);
	
}


cPlayer::~cPlayer()
{
}

void cPlayer::Update()
{
	int V_STRAIGHT = 3;
	int V_DIAGONAL = 2;

	cInputLayer  &input = cGame::Instance()->Input;

	int vecx = 0;
	int vecy = 0;

	//Miro si haig de moure'm
	if (input.KeyDown(DIK_W))	vecy--;
	if (input.KeyDown(DIK_S))	vecy++;
	if (input.KeyDown(DIK_A))	vecx--;
	if (input.KeyDown(DIK_D))	vecx++;

	//Si no m'he mogut FORA!
	if (!vecy && !vecx)
	{

	}
	else
	{
		// Busco l'orientacio del moviment
		if (vecy == 0)
		{
			if (vecx > 0)		m_orientation = ORIENTATION_E;
			else if (vecx < 0)	m_orientation = ORIENTATION_O;
		}
		else if (vecy > 0)
		{
			if (vecx > 0)		m_orientation = ORIENTATION_SE;
			else if (vecx < 0)	m_orientation = ORIENTATION_SO;
			else				m_orientation = ORIENTATION_S;
		}
		else
		{
			if (vecx > 0)		m_orientation = ORIENTATION_NE;
			else if (vecx < 0)	m_orientation = ORIENTATION_NO;
			else				m_orientation = ORIENTATION_N;
		}

		int x, y;
		GetPosition(x,y);

		//Actualitzo el moviment segons orientacio
		switch (m_orientation)
		{
		case ORIENTATION_N:
			y -= V_STRAIGHT;
			break;
		case ORIENTATION_NE:
			y -= V_DIAGONAL;
			x += V_DIAGONAL;
			break;
		case ORIENTATION_NO:
			y -= V_DIAGONAL;
			x -= V_DIAGONAL;
			break;
		case ORIENTATION_S:
			y += V_STRAIGHT;
			break;
		case ORIENTATION_SE:
			y += V_DIAGONAL;
			x += V_DIAGONAL;
			break;
		case ORIENTATION_SO:
			y += V_DIAGONAL;
			x -= V_DIAGONAL;
			break;
		case ORIENTATION_E:
			x += V_STRAIGHT;
			break;
		case ORIENTATION_O:
			x -= V_STRAIGHT;
			break;
		}
	
		SetPosition(x, y);
	}
	cBaseEntity::Update();
}

void cPlayer::Render()
{
	cBaseEntity::Render();
	
}