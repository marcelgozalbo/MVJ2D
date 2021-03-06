
#include "cMenu.h"
#include "cBaseEntity.h"
#include "cGame.h"
#include "cMouse.h"
#include <iostream>

static const int TIME_ARROW_BLINK = 700;
static const int TIME_ENABLE_INPUT = 200;

typedef std::chrono::duration<int, std::milli> millisecs_t;

cMenu::cMenu() :
	_background(nullptr),
	_greenArrows(nullptr),
	_selection(cMenu::SELECTION_PLAY),
	_start(std::chrono::high_resolution_clock::now()),
	_blink(false)
{
}

cMenu::~cMenu()
{
	delete _background;
	delete _greenArrows;
}

void cMenu::LoadData()
{
	_background = new cBaseEntity;
	_background->SetTextureID(std::string("main"));

	_greenArrows = new cBaseEntity;
	_greenArrows->SetTextureID(std::string("green_arrow"));
	_greenArrows->SetZIndex(1);
	UpdatePositionArrow();
}

bool cMenu::Update()
{
	bool returnValue = true;
	cInputLayer  &input = cGame::Instance()->Input;

	if (input.KeyUpDown(DIK_RETURN))
	{
		if (_selection == cMenu::SELECTION_PLAY)
		{
			cGame::Instance()->SetState(STATE_GAME);
		}
		else if (_selection == cMenu::SELECTION_EXIT)
		{
			cGame::Instance()->SetState(STATE_FINISHED);
		}
	}
	else if (input.KeyUpDown(DIK_DOWN))
	{
		if (_selection < SELECTION_EXIT)
		{
			_selection = static_cast<cMenu::eSelection>(static_cast<char>(_selection)+1);
			UpdatePositionArrow();
		}
	}
	else if (input.KeyUpDown(DIK_UP))
	{
		if (_selection > SELECTION_PLAY)
		{
			_selection = static_cast<cMenu::eSelection>(static_cast<char>(_selection)-1);
			UpdatePositionArrow();
		}
	}

	if (millisecs_t(std::chrono::duration_cast<millisecs_t>(std::chrono::high_resolution_clock::now() - _start)).count() > (_blink ? TIME_ARROW_BLINK  : TIME_ARROW_BLINK + 200))
	{
		ToBlinkArrow();
		_start = std::chrono::high_resolution_clock::now();
	}

	return returnValue;
}

bool cMenu::Render()
{
	_background->Render();
	_greenArrows->Render();
	/*
	// Example font
	cRectangle Rectangle;
	Rectangle.SetRect(10);
	Rectangle.w = 100;
	Rectangle.h = 50;
	cGame::Instance()->Graphics->DrawFont("arial", "puteruuuuuuuuuuuuuuuu", 100, Rectangle);// , 0xFF000000, DT_VCENTER);
	*/
	return true;
}

void cMenu::StartBlinkArrow()
{
	_blink = true;
	_start = std::chrono::high_resolution_clock::now();
	ToBlinkArrow();
}

void cMenu::ToBlinkArrow()
{
	_greenArrows->SetVisible(_blink);
	_blink = !_blink;
}

void cMenu::UpdatePositionArrow()
{
	if (_selection == SELECTION_PLAY)
	{
		_greenArrows->SetPosition(175, 210);
	}
	else if (_selection == SELECTION_EXIT)
	{
		_greenArrows->SetPosition(175, 325);
	}

	StartBlinkArrow();
}
