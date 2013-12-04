
#include "cGame.h"
#include "cLog.h"
#include "cMouse.h"

cGame* cGame::_instance = 0;

cGame* cGame::Instance()
{
	if (_instance == 0)
	{
		_instance = new cGame;
	}
	return _instance;
}

cGame::cGame() :
_state(STATE_MAIN)
{
}
cGame::~cGame()
{
	delete Scene;
	delete Graphics;

}

bool cGame::Init(HWND hWnd,HINSTANCE hInst,bool exclusive)
{
	bool res;
	cLog *Log = cLog::Instance();

	Graphics = new cGraphicsLayer();
	res = Graphics->Init(hWnd, exclusive);
	if(!res)
	{
		Log->Msg("Error initializing Graphics!");
		return false;
	}

	res = Input.Init(hInst,hWnd,exclusive,USE_KEYBOARD);
	if(!res)
	{
		Log->Msg("Error initializing Input!");
		return false;
	}
	Input.SetMousePosition(SCREEN_RES_X >> 1,SCREEN_RES_Y >> 1);

	Graphics->LoadData();

	Scene = new cScene();
	Scene->LoadMap("../media/map.txt");

	Menu.LoadData();

	return true;
}

void cGame::Finalize()
{
	Graphics->UnLoadData();
	Graphics->Finalize();
	Input.UnacquireAll();
	Input.Finalize();
}

void cGame::SetState(eGameStates aState)
{
	_state = aState;
}

bool cGame::Loop()
{
	if (_state == STATE_FINISHED)
		return false;
	bool res;
	//Input
	res = LoopInput();
	//if(!res) return false;
	//Process
	res = LoopProcess();
	//if (!res) return false;
	//Output
	res = LoopOutput();
	//if(!res) return false;
	return true;
}

bool cGame::LoopInput()
{
	bool res;
	cLog *Log = cLog::Instance();

	res = Input.Read();
	if(!res)
	{
		Log->Msg("Error reading Input!");
		return false;
	}
	return true;
}

bool cGame::LoopProcess()
{
	switch(_state)
	{
		case STATE_MAIN:
						Menu.Update();
						break;

		case STATE_GAME:
						ProcessOrder();
						Critter.Move();
						break;
	}
	return true;
}

bool cGame::LoopOutput()
{
	bool res;
	res = Render();
	return res;
}

bool cGame::Render()
{
	bool res = true;
	switch (_state)
	{
	case STATE_MAIN:
		Menu.Render();
		break;

	case STATE_GAME:
		Scene->Render();
		break;
	}
	Graphics->Render();
	return true;
}


void cGame::ProcessOrder()
{
	cMouse *Mouse;
	cKeyboard *Keyboard;
	int mx, my, msx, msy, p, cx, cy, x, y;
	int s = 5; //marge for directional pointers
	int xo, xf, yo, yf;
	int b4pointer;
	static int release_and_press;

	Mouse = Input.GetMouse();
	if (Mouse)
	{
		//Keyboard = Input.GetKeyboard();
		b4pointer = Mouse->GetPointer();
		Mouse->GetPosition(&mx, &my);

		//Actualitzo el jugador
		Critter.Update();

	}
}