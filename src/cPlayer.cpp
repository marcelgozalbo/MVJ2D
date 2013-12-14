#include "cPlayer.h"

#include "cGame.h"
cPlayer::cPlayer():
	cCharacter("player", cRectangle(0, 0, 16, 24), 0, 0, 10, 3, 2, 3.0f)
{
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

	SetAnimationSteps(m_LeftShield);
	SetAnimationFramesPerStep(5);
	EnableAnimation();
	PlayAnimation();	

	EnableDebugMode();
}


cPlayer::~cPlayer()
{

}

void cPlayer::Update()
{
	cInputLayer  &input = cGame::Instance()->Input;

	int vecx = 0;
	int vecy = 0;

	//Miro si haig de moure'm
	if (input.KeyDown(DIK_W))	vecy--;
	if (input.KeyDown(DIK_S))	vecy++;
	if (input.KeyDown(DIK_A))	vecx--;
	if (input.KeyDown(DIK_D))	vecx++;

	// Si m'haig de moure
	if (vecx || vecy)
	{
		Move(vecx, vecy);

		//CAnvio l'animacio segons l'orientacio
		if (GetLastOrientation() != GetCurrentOrientation())
		{
			/*{
			int x, y, z;
			GetPosition(x, y);
			GetZIndex(z);
			cGame::Instance()->Graphics->DrawFont("arial", "SET O", z + 1, cRectangle(x - 40, y, 0, 0));
			}
			*/
			auto orient = GetCurrentOrientation();
			switch (orient)
			{
				case ORIENTATION_N:
				case ORIENTATION_NE:
				case ORIENTATION_NO:
					SetAnimationSteps(m_Up);
					break;
				case ORIENTATION_S:
				case ORIENTATION_SE:
				case ORIENTATION_SO:
					SetAnimationSteps(m_Down);
					break;
				case ORIENTATION_E:
					SetAnimationSteps(m_Right);
					break;
				case ORIENTATION_O:
					SetAnimationSteps(m_Left);
					break;
				default:
					break;
			}

		}
		
		PlayAnimation();
	}
	else
	{
		ResetAnimation();
		StopAnimation();
	}
	
	cBaseEntity::Update();
}

void cPlayer::Render()
{
	cBaseEntity::Render();
	
}
