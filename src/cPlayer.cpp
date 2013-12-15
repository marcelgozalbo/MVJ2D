#include "cPlayer.h"

#include "cGame.h"
cPlayer::cPlayer():
	cCharacter("player", cRectangle(0, 0, 16, 24), 0, 0, 10,3, 2, 3.0f)
{
	m_StepsOrder = {5,6,5,4,1,0,1,2};
	m_IdleStep = { 3 };

	m_Down.push_back(cRectangle(0, 0, 16, 24));
	m_Down.push_back(cRectangle(23, 0, 16, 24));
	m_Down.push_back(cRectangle(47, 0, 16, 24));
	m_Down.push_back(cRectangle(70, 0, 16, 24));
	m_Down.push_back(cRectangle(93, 0, 16, 24));
	m_Down.push_back(cRectangle(117, 0, 16, 24));
	m_Down.push_back(cRectangle(140, 0, 16, 24));
	
	m_DownShield.push_back(cRectangle(0, 30, 16, 24));
	m_DownShield.push_back(cRectangle(23, 30, 16, 24));
	m_DownShield.push_back(cRectangle(47, 30, 16, 24));
	m_DownShield.push_back(cRectangle(70, 30, 16, 24));
	m_DownShield.push_back(cRectangle(93, 30, 16, 24));
	m_DownShield.push_back(cRectangle(117, 30, 16, 24));
	m_DownShield.push_back(cRectangle(140, 30, 16, 24));

	m_Up.push_back(cRectangle(0, 60, 16, 24));
	m_Up.push_back(cRectangle(23, 60, 16, 24));
	m_Up.push_back(cRectangle(47, 60, 16, 24));
	m_Up.push_back(cRectangle(70, 60, 16, 24));
	m_Up.push_back(cRectangle(93, 60, 16, 24));
	m_Up.push_back(cRectangle(117, 60, 16, 24));
	m_Up.push_back(cRectangle(140, 60, 16, 24));

	m_UpShield.push_back(cRectangle(0, 90, 16, 24));
	m_UpShield.push_back(cRectangle(23, 90, 16, 24));
	m_UpShield.push_back(cRectangle(47, 90, 16, 24));
	m_UpShield.push_back(cRectangle(70, 90, 16, 24));
	m_UpShield.push_back(cRectangle(93, 90, 16, 24));
	m_UpShield.push_back(cRectangle(117, 90, 16, 24));
	m_UpShield.push_back(cRectangle(140, 90, 16, 24));

	m_Right.push_back(cRectangle(0, 120, 16, 24));
	m_Right.push_back(cRectangle(23, 120, 16, 24));
	m_Right.push_back(cRectangle(47, 120, 16, 24));
	m_Right.push_back(cRectangle(70, 120, 16, 24));
	m_Right.push_back(cRectangle(93, 120, 16, 24));
	m_Right.push_back(cRectangle(117, 120, 16, 24));
	m_Right.push_back(cRectangle(140, 120, 16, 24));

	m_RightShield.push_back(cRectangle(2, 150, 17, 23));
	m_RightShield.push_back(cRectangle(25, 150, 17, 24));
	m_RightShield.push_back(cRectangle(50, 150, 18, 24));
	m_RightShield.push_back(cRectangle(72, 150, 18, 24));
	m_RightShield.push_back(cRectangle(96, 150, 18, 24));
	m_RightShield.push_back(cRectangle(120, 150, 17, 24));
	m_RightShield.push_back(cRectangle(142, 150, 18, 24));

	m_Left.push_back(cRectangle(3, 179, 17, 24));
	m_Left.push_back(cRectangle(26, 179, 16, 24));
	m_Left.push_back(cRectangle(50, 179, 16, 24));
	m_Left.push_back(cRectangle(74, 179, 16, 24));
	m_Left.push_back(cRectangle(96, 179, 16, 24));
	m_Left.push_back(cRectangle(121, 179, 16, 24));
	m_Left.push_back(cRectangle(144, 179, 16, 24));

	m_LeftShield.push_back(cRectangle(0, 209, 18, 24));
	m_LeftShield.push_back(cRectangle(23, 209, 17, 24));
	m_LeftShield.push_back(cRectangle(46, 209, 18, 24));
	m_LeftShield.push_back(cRectangle(70, 209, 18, 24));
	m_LeftShield.push_back(cRectangle(90, 209, 18, 24));
	m_LeftShield.push_back(cRectangle(118, 209, 17, 24));
	m_LeftShield.push_back(cRectangle(141, 209, 17, 24));

	
	m_DownSword.push_back(cRectangle(0, 238, 20, 23));
	m_DownSword.push_back(cRectangle(25, 238, 21, 30));
	m_DownSword.push_back(cRectangle(54, 238, 20, 32));
	m_DownSword.push_back(cRectangle(80, 238, 20, 33));
	m_DownSword.push_back(cRectangle(104, 238, 28, 31));
	m_DownSword.push_back(cRectangle(135, 238, 32, 29));
	
	SetAnimationRects(m_LeftShield);
	SetAnimationOrderSteps(m_StepsOrder);
	SetAnimationFramesPerStep(5);
	EnableAnimation();
	PlayAnimation();	

	EnableDebugMode();

	
	m_state = E_IDLE;
}


cPlayer::~cPlayer()
{
	

}

void cPlayer::UpdateIdle()
{
	

	auto orient = GetCurrentOrientation();
	switch (orient)
	{
	case ORIENTATION_N:
	case ORIENTATION_NE:
	case ORIENTATION_NO:
		SetAnimationRects(m_Up);
		break;
	case ORIENTATION_S:
	case ORIENTATION_SE:
	case ORIENTATION_SO:
		SetAnimationRects(m_Down);
		break;
	case ORIENTATION_E:
		SetAnimationRects(m_Right);
		break;
	case ORIENTATION_O:
		SetAnimationRects(m_Left);
		break;
	default:
		break;
	}
	
	//Setejo el Frame que esta quiet i paro
	SetAnimationOrderSteps(m_IdleStep);




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
				m_state = E_MOVE;

			if (input.KeyDown(DIK_SPACE))
				m_state = E_ATTACKING;
		}
		break;
	case E_MOVE:
		if (input.KeyDown(DIK_W) || input.KeyDown(DIK_A) ||
			input.KeyDown(DIK_D) || input.KeyDown(DIK_S))
			m_state = E_MOVE;
		else
			m_state = E_IDLE;

		if (input.KeyDown(DIK_SPACE))
			m_state = E_ATTACKING;
		break;
	case E_ATTACKING:
		if (GetAnimationCurrentStep() == GetAnimationOrderStepsCount() - 1)
			m_state = E_IDLE;
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
	cInputLayer  &input = cGame::Instance()->Input;
	
	/*{
	int x, y, z;
	GetPosition(x, y);
	GetZIndex(z);
	cGame::Instance()->Graphics->DrawFont("arial", "DINS O", z + 1, cRectangle(x - 40, y, 0, 0));
	}*/
	static bool started_attacking = false;

	if (!started_attacking)
	{
		auto orient = GetCurrentOrientation();
		switch (orient)
		{
		case ORIENTATION_N:
		case ORIENTATION_NE:
		case ORIENTATION_NO:
			SetAnimationRects(m_DownSword);
			break;
		case ORIENTATION_S:
		case ORIENTATION_SE:
		case ORIENTATION_SO:
			SetAnimationRects(m_DownSword);
			break;
		case ORIENTATION_E:
			SetAnimationRects(m_DownSword);
			break;
		case ORIENTATION_O:
			SetAnimationRects(m_DownSword);
			break;
		default:
			break;
		}
		PlayAnimation();
		started_attacking = true;
	}
	
	
	
	
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
	// Si m'haig de moure
	static bool first_enter = true;
	if (vecx || vecy)
	{
		MovePlayer(vecx, vecy);

		//CAnvio l'animacio segons l'orientacio
		if ((GetLastOrientation() != GetCurrentOrientation()) || first_enter)
		{
			/*{
			int x, y, z;
			GetPosition(x, y);
			GetZIndex(z);
			cGame::Instance()->Graphics->DrawFont("arial", "DINS O", z + 1, cRectangle(x - 40, y, 0, 0));
			}*/

			auto orient = GetCurrentOrientation();
			switch (orient)
			{
			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationRects(m_Up);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationRects(m_Down);
				break;
			case ORIENTATION_E:
				SetAnimationRects(m_Right);
				break;
			case ORIENTATION_O:
				SetAnimationRects(m_Left);
				break;
			default:
				break;
			}
			//Setejo l'ordre.
			SetAnimationOrderSteps(m_StepsOrder);
			first_enter = false;
		}

	}
	else
	{
		first_enter = true;
	}

}

void cPlayer::Render()
{
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

		if (game->Scene->m_map.movePlayer(destRect))
		{
			SetPosition(x, y);
		}
	}
}
