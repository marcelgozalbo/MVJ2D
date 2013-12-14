
#ifndef __GAME_H__
#define __GAME_H__

#include "types.h"
#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "cSound.h"
#include "cMenu.h"
#include "DebugUtils.h"

enum eGameStates
{
	STATE_MAIN,
	STATE_GAME,
	STATE_PAUSED,
	STATE_FINISHED,
	STATE_NUMBER
};

struct Globals
{
	struct Limits
	{
		u32 minX = 0;
		u32 minY = 0;
		u32 maxX = 1024;
		u32 maxY = 1024;

		bool inside(u32 x, u32 y) const { return x >= minX && x <= maxX && y >= minY && y <= maxY; }
	};

	Limits limits;
};

class cGame
{
public:
	static cGame* Instance();
	virtual ~cGame();

	bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
	bool Loop(); 
	void Finalize();
	void SetState(eGameStates aState);

	static const Globals globals;

	cInputLayer Input;
	cScene *Scene;
	cGraphicsLayer *Graphics;
	cMenu Menu;

private:
	cGame();
	static cGame* _instance; //singleton
	bool LoopInput();
	bool LoopProcess();
	bool LoopOutput();

	cSound Sound;
	
	eGameStates _state;

	bool Render();
};

#endif
