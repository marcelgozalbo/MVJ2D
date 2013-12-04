
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "cSound.h"
#include "cMenu.h"

enum eGameStates
{
	STATE_MAIN,
	STATE_GAME,
	STATE_FINISHED,
	STATE_NUMBER
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
