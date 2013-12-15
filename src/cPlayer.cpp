#include "cPlayer.h"

#include "cGame.h"
cPlayer::cPlayer():
	cCharacter("player", cRectangle(0, 0, 16, 24), 0, 0, 10,3, 2, 2.0f)
{
	m_StepsOrder = {5,6,5,4,1,0,1,2};
	m_IdleStep = { 3 };
	m_life_count = 5;
	

	LoadSteps(m_DownSword, 0, 0, 6, 64, 64);
	LoadSteps(m_UpSword, 0, 325, 6, 64, 64);
	LoadSteps(m_RightSword, 0, 260, 6, 64, 64);
	LoadSteps(m_LeftSword, 0, 455, 6, 64, 64);

	LoadSteps(m_DownShield,0,65,7,64,64);
	LoadSteps(m_UpShield, 0, 130, 7, 64, 64);
	LoadSteps(m_RightShield, 0, 195, 7, 64, 64);
	LoadSteps(m_LeftShield, 0, 390, 7, 64, 64);
	
	SetTextureSizeToCollisionRectRelative();
	



	SetAnimationFramesPerStep(3);

	EnableAnimation();
	PlayAnimation();	

	EnableDebugMode();
	ChangeToIdle();

	cRectangle r(24,24,14,16);
	SetCollisionRectRelative(r);


	
}
void cPlayer::DrawLife()
{

	cRectangle r(456,1,32,28);	
	for (int i = 0; i < m_life_count;i++)
		cGame::Instance()->Graphics->DrawSprite("player", i*40, 0, 11, r);

}

void cPlayer::LoadSteps(std::vector<cRectangle> &outvec, int startx, int starty, int numsteps, int ampladaframe, int alturaframe)
{
	int offsetquadratx = ampladaframe + 1;
	int offsetquadraty = alturaframe + 1;
	for (int i = 0; i < numsteps; i++)
		outvec.push_back(cRectangle((i*offsetquadratx) + 2, starty + 2, ampladaframe - 2, alturaframe - 2));
}


cPlayer::~cPlayer()
{
	

}

void cPlayer::UpdateIdle()
{
	PlayAnimation();
}

void cPlayer::SetTextureFromOrientation()
{
	auto orient = GetCurrentOrientation();
	
	switch (m_state)
	{
		case E_IDLE:
		{
			switch (orient)
			{

			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationRects(m_UpShield);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationRects(m_DownShield);
				break;
			case ORIENTATION_E:
				SetAnimationRects(m_RightShield);
				break;
			case ORIENTATION_O:
				SetAnimationRects(m_LeftShield);
				break;
			default:
				break;
			}
			//Setejo el Frame que esta quiet i paro
			SetAnimationOrderSteps(m_IdleStep);
		}
			break;

		case E_ATTACKING:
		{
			auto recabsplayer = GetCollisionRectAbsolute();
			switch (orient)
			{

			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationRects(m_UpSword);
				m_attack_col_rect.SetRect(recabsplayer.x, recabsplayer.y -30, recabsplayer.w, 30);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationRects(m_DownSword);
				m_attack_col_rect.SetRect(recabsplayer.x, recabsplayer.y + recabsplayer.h, recabsplayer.w, 30);
				break;
			case ORIENTATION_E:
				SetAnimationRects(m_RightSword);
				m_attack_col_rect.SetRect(recabsplayer.x + recabsplayer.w, recabsplayer.y, 30, recabsplayer.h);
				break;
			case ORIENTATION_O:
			{

				SetAnimationRects(m_LeftSword);
				//HAck per no canviar el png
				std::vector<u32> buf;
				for (int i = GetAnimationOrderStepsCount() - 1; i >= 0; i--)
					buf.push_back(i);
				SetAnimationOrderSteps(buf);

				m_attack_col_rect.SetRect(recabsplayer.x - 30, recabsplayer.y, 30, recabsplayer.h);


				


			}
				break;
			default:
				break;
			}
			PlayAnimationNoLoop();
			

		}
			break;
		case E_MOVE:
		{
			switch (orient)
			{

			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationRects(m_UpShield);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationRects(m_DownShield);
				break;
			case ORIENTATION_E:
				SetAnimationRects(m_RightShield);
				break;
			case ORIENTATION_O:
				SetAnimationRects(m_LeftShield);
				break;
			default:
				break;
			}
			//Setejo el Frame que esta quiet i paro
			SetAnimationOrderSteps(m_StepsOrder);
		}
			break;


		
	
	}
	


}
void cPlayer::ChangeToIdle()
{
	
	m_state = E_IDLE;
	SetTextureFromOrientation();


}

void cPlayer::ChangeToAttack()
{
	m_state = E_ATTACKING;
	SetTextureFromOrientation();

}




void cPlayer::Update()
{
	cInputLayer  &input = cGame::Instance()->Input;


	//Agafo Input segons estat
	switch (m_state)
	{
	case E_IDLE:
		{
				   if (input.KeyDown(DIK_W) || input.KeyDown(DIK_A) ||
					   input.KeyDown(DIK_D) || input.KeyDown(DIK_S))
					   ChangeToMove();

				   if (input.KeyDown(DIK_SPACE))
					   ChangeToAttack();
		}
		break;
	case E_MOVE:
		if (input.KeyDown(DIK_W) || input.KeyDown(DIK_A) ||
			input.KeyDown(DIK_D) || input.KeyDown(DIK_S))
		{}
		else
			ChangeToIdle();

		if (input.KeyDown(DIK_SPACE))
			ChangeToAttack();

		break;
	case E_ATTACKING:
		if (IsAnimationLoopFinished())
			ChangeToIdle();
		break;

	}


	switch (m_state)
	{
	case E_IDLE:
		UpdateIdle();
		break;
	case E_MOVE:
		UpdateMovement();
		break;
	case E_ATTACKING:
		UpdateAttack();
		break;

	}
	



	cBaseEntity::Update();
}

void cPlayer::UpdateAttack()
{
	
	cGame* game = cGame::Instance();
	cScene *sc = cGame::Instance()->Scene;
	
	//Renderitzo el rectangle a Z+1 perque surti per sobre la textura sempre
	int z;
	GetZIndex(z);
	cGame::Instance()->Graphics->DrawRect(m_attack_col_rect, 0x00FF00FF, z + 1);
	sc->UpdateEnemyHit(m_attack_col_rect);
	/*{
	int x, y, z;
	GetPosition(x, y);
	GetZIndex(z);
	cGame::Instance()->Graphics->DrawFont("arial", "DINS O", z + 1, cRectangle(x - 40, y, 0, 0));
	}*/
	

}

void cPlayer::ChangeToMove()
{
	/*{
		int x, y, z;
		GetPosition(x, y);
		GetZIndex(z);
		cGame::Instance()->Graphics->DrawFont("arial", "MOVE", z + 1, cRectangle(x - 40, y+40, 0, 0));
	}
	*/
	
	
	m_state = E_MOVE;
	SetTextureFromOrientation();


}

void cPlayer::UpdateMovement()
{
	cInputLayer  &input = cGame::Instance()->Input;
	int vecx = 0;
	int vecy = 0;

	if (input.KeyDown(DIK_W))	vecy--;
	if (input.KeyDown(DIK_S))	vecy++;
	if (input.KeyDown(DIK_A))	vecx--;
	if (input.KeyDown(DIK_D))	vecx++;

	//static bool last_stop = true;
	if (vecx || vecy)
	{
		MovePlayer(vecx, vecy);

		if (GetCurrentOrientation() != GetLastOrientation())
		{
			SetTextureFromOrientation();
			/*{
			int x, y, z;
			GetPosition(x, y);
			GetZIndex(z);
			cGame::Instance()->Graphics->DrawFont("arial", "DINS O", z + 1, cRectangle(x - 40, y, 0, 0));
			*/
		}
		

	}

}

void cPlayer::Render()
{
	DrawLife();
	cBaseEntity::Render();
	
}

void cPlayer::MovePlayer(s32 xAmount, s32 yAmount)
{
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



		int x = 0;
		int y = 0;
		

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
		destRect.x += x;
		destRect.y += y;

		cGame* game = cGame::Instance();

		if (game->Scene->m_map.movePlayer(destRect))
		{
			int xlast, ylast;
			GetPosition(xlast, ylast);
			SetPosition(x+xlast, y+ylast);
		}
	}
}
