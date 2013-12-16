#include "cHeart.h"
#include "cGame.h"

cHeart::cHeart(s32 x, s32 y) :
	cBaseEntity(),
	_heart_sound(0)
{
	cRectangle textureRect(456, 1, 32, 28);
	cRectangle collRect(0, 0, 32, 28);

	SetPosition(x, y);
	SetZIndex(10);
	SetTextureID("player");
	SetTextureRect(textureRect);
	SetTextureScale(1.0f);

	EnableCollision();

	SetCollisionRectRelative(collRect);
	

	EnableDebugMode();
	EnableColDebugMode();
	EnableDebugPosMode();

	_heart_sound = cGame::Instance()->Sound.LoadSound("../media/heart.wav");
	cGame::Instance()->Sound.SetVolumeSound(_heart_sound, 1.0f);
}

cHeart::~cHeart()
{

}

void cHeart::get()
{
	cGame::Instance()->Sound.PlayGameSound(_heart_sound);
}
