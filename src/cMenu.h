
#ifndef __MENU_H__
#define __MENU_H__

#include "cBaseEntity.h"

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
	cBaseEntity* _background;
	cBaseEntity* _greenArrows;
	eSelection _selection;
};

#endif 
