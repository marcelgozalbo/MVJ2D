#include "cHeart.h"
#include "Utils.h"
#include "cLog.h"

cHeart::cHeart(s32 x, s32 y) :
	cBaseEntity()
{
	cRectangle textureRect(456, 1, 32, 28);
	cRectangle collRect(0, 0, 32, 28);

	SetPosition(x, y);
	SetZIndex(10);
	SetTextureID("player");
	SetTextureRect(textureRect);
	SetTextureScale(1.0f);

	EnableCollision();

	//SetTextureSizeToCollisionRectRelative();

	SetCollisionRectRelative(collRect);
	

	EnableDebugMode();
	EnableColDebugMode();
	EnableDebugPosMode();

	LOG("heart posx: " + util::toString(x) + " posy: " + util::toString(y));
}

cHeart::~cHeart()
{

}
