
#include "cMenu.h"
#include "cBaseEntity.h"
#include "cGame.h"
#include "cMouse.h"

/*#include "cMouse.h"
#include <stdio.h>
#include <iostream>
#include "cGame.h"*/

cMenu::cMenu() :
	_background(nullptr),
	_greenArrows(nullptr),
	_selection(cMenu::SELECTION_PLAY)
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
	_background->SetTextureID(std::string("mainmenu"));

	_greenArrows = new cBaseEntity;
	_greenArrows->SetTextureID(std::string("green_arrow"));
	_greenArrows->SetZIndex(1);
	_greenArrows->SetPosition(0, 0);
}

bool cMenu::Update()
{
	bool returnValue = true;
	cInputLayer  &input = cGame::Instance()->Input;

	if (input.KeyDown(DIK_RETURN))
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
	else if (input.KeyDown(DIK_DOWN))
	{
		_selection = static_cast<cMenu::eSelection>((static_cast<char>(_selection)+1) % cMenu::SELECTION_NUMBER);
	}
	else if (input.KeyDown(DIK_UP))
	{
		_selection = static_cast<cMenu::eSelection>((static_cast<char>(_selection)-1) % cMenu::SELECTION_NUMBER);
	}

	return returnValue;
}

bool cMenu::Render()
{
	_background->Render();
	_greenArrows->Render();
	return true;
}
