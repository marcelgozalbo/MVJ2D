
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"

#define STATE_MAIN	0
#define STATE_GAME	1

class cGame
{
public:
	static cGame* Instance();
	virtual ~cGame();

	bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
	bool Loop(); 
	void Finalize();

	cInputLayer Input;
	cScene Scene;
	cGraphicsLayer Graphics;
	cCritter Critter;
	cSkeleton Skeleton;

private:
	cGame();
	static cGame* _instance; //singleton
	bool LoopInput();
	bool LoopProcess();
	bool LoopOutput();

	
	int state;

	void ProcessOrder();

	bool Render();
};

#endif
