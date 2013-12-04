#pragma once

#include "cBaseEntity.h"
/*
typedef enum
{
	ORIENTATION_N = 0,
	ORIENTATION_NE,
	ORIENTATION_NO,
	ORIENTATION_S,
	ORIENTATION_SE,
	ORIENTATION_SO,
	ORIENTATION_E,
	ORIENTATION_O,

}CritterOrientation;
*/
class cPlayer: public cBaseEntity
{
public:
	cPlayer();


	virtual void Update();
	virtual void Render();

	virtual ~cPlayer();

	
};

