#ifndef MPV2D_CHEART_H_
#define MPV2D_CHEART_H_

#include "cBaseEntity.h"
#include "cSound.h"

class cHeart : public cBaseEntity
{
public:
	cHeart(s32 x, s32 y);
	virtual ~cHeart();

	void get();

private:
	cSound::tSoundId _heart_sound;
};

#endif
