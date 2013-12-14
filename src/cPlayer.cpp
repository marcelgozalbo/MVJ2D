#include "cPlayer.h"

#include "cGame.h"
cPlayer::cPlayer():
	cCharacter("player", cRectangle(0, 0, 16, 24), 0, 0, 10, 3, 2, 3.0f)
{
	std::vector<cRectangle> Animations;
	Animations.push_back(cRectangle(0, 0, 16, 24));
	Animations.push_back(cRectangle(23,0, 16, 24));
	Animations.push_back(cRectangle(47, 0, 16, 24));
	Animations.push_back(cRectangle(70, 0, 16, 24));
	Animations.push_back(cRectangle(93, 0, 16, 24));
	Animations.push_back(cRectangle(117, 0, 16, 24));
	Animations.push_back(cRectangle(140, 0, 16, 24));
	
	std::vector<cRectangle> DownShield;
	DownShield.push_back(cRectangle(0, 30, 16, 24));
	DownShield.push_back(cRectangle(23, 30, 16, 24));
	DownShield.push_back(cRectangle(47, 30, 16, 24));
	DownShield.push_back(cRectangle(70,30, 16, 24));
	DownShield.push_back(cRectangle(93, 30, 16, 24));
	DownShield.push_back(cRectangle(117, 30, 16, 24));
	DownShield.push_back(cRectangle(140, 30, 16, 24));

	SetAnimationSteps(DownShield);
	SetAnimationFramesPerStep(5);
	EnableAnimation();
	PlayAnimation();	
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

	Move(vecx, vecy);

	cBaseEntity::Update();
}

void cPlayer::Render()
{
	cBaseEntity::Render();
	
}
