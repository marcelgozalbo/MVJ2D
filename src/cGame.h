
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
	STATE_ENDGAMEGOOD,
	STATE_ENDGAMELOST,
	STATE_NUMBER
};

struct Globals
{
	struct Limits
	{
		s32 minX = 0;
		s32 minY = 0;
		s32 maxX = 1024;
		s32 maxY = 1024;

		bool inside(s32 x, s32 y) const { return x >= minX && x <= maxX && y >= minY && y <= maxY; }
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

	cSound Sound;

private:
	cGame();
	static cGame* _instance; //singleton
	bool LoopInput();
	bool LoopProcess();
	bool LoopOutput();

	eGameStates _state;
	cSound::tSoundId _loop_sound_id;
	cSound::tSoundId _win_sound;
	cSound::tSoundId _lose_sound;
 
	bool Render();
};

#endif
