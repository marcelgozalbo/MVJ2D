
#include "cGame.h"
#include "cLog.h"
#include "cMouse.h"

cGame* cGame::_instance = 0;
const Globals cGame::globals;

cGame* cGame::Instance()
{
	if (_instance == 0)
	{
		_instance = new cGame;
	}
	return _instance;
}

cGame::cGame() :
	_state(STATE_MAIN),
	_loop_sound_id(0)
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

	Log->Clear();

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
	Scene->LoadEnemies();

	Menu.LoadData();

	_loop_sound_id = Sound.LoadSound("../media/back_music.mp3");
	Sound.PlayGameSound(_loop_sound_id, true);
	Sound.SetVolumeSound(_loop_sound_id, 1.0);
	Sound.PauseSound(_loop_sound_id);

	return true;
}

void cGame::Finalize()
{
	if (_instance)
	{
		Graphics->UnLoadData();
		Graphics->Finalize();
		Input.UnacquireAll();
		Input.Finalize();
		cLog::Release();

		delete _instance;
	}
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
		//Log->Msg("Error reading Input!");
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
						Scene->Update();
						if (Input.KeyUpDown(DIK_P))
						{
							_state = STATE_PAUSED;
							Sound.SetVolumeSound(_loop_sound_id, 0.1f);
						}
						if (Scene->IsPlayerLost())
							_state = STATE_ENDGAMELOST;

						if (Scene->IsPlayerWon())
							_state = STATE_ENDGAMEGOOD;
							
						break;
		case STATE_PAUSED:
						if (Input.KeyUpDown(DIK_RETURN))
						{
							_state = STATE_GAME;
							Sound.SetVolumeSound(_loop_sound_id, 1.0f);
						}
						break;
		case 	STATE_ENDGAMEGOOD:
		case STATE_ENDGAMELOST:
			if (Input.KeyDown(DIK_RETURN))
			{
				Scene->m_map.reset();

				Scene->m_player.respawn();
				Scene->m_player.SetPosition(0, 0);

				Scene->m_enemies.clear();
				Scene->LoadEnemies();

				_state = STATE_MAIN;
			
			}
			break;
	}

	if (Input.KeyDown(DIK_ESCAPE))
	{
		_state = STATE_FINISHED;
	}
	else if (Input.KeyUpDown(DIK_M))
	{
		Sound.ToggleSound(_loop_sound_id);
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
	case STATE_PAUSED:
		cGame::Instance()->Graphics->DrawSprite("paused", 0, 0, 100, cRectangle(0,0,800,600));
	case STATE_GAME:
		Scene->Render();
		break;
	case 	STATE_ENDGAMEGOOD:
			cGame::Instance()->Graphics->DrawSprite("win", 0, 0, 100, cRectangle(0, 0, 1024, 768),0.8f,0.8f);
		
		break;
	case STATE_ENDGAMELOST:
		cGame::Instance()->Graphics->DrawSprite("lose", 0, 0, 100, cRectangle(0, 0, 1024, 768), 0.65f, 0.8f);
			break;

	}
	Graphics->Render();
	return true;
}

