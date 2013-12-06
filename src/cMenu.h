
#ifndef __MENU_H__
#define __MENU_H__

#include "cBaseEntity.h"
#include <chrono>

class cMenu
{
	enum eSelection
	{
		SELECTION_PLAY,
		SELECTION_EXIT,
		SELECTION_NUMBER
	};

public:
	cMenu();
	~cMenu();
	void LoadData();
	bool Update();
	bool Render();

private:
	void UpdatePositionArrow();
	void StartBlinkArrow();
	void ToBlinkArrow();

	cBaseEntity* _background;
	cBaseEntity* _greenArrows;
	eSelection _selection;
	std::chrono::high_resolution_clock::time_point _start;
	bool _blink;
};

#endif 
