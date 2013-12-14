
#ifndef __SCENE_H__
#define __SCENE_H__

#include "cPlayer.h"
#include "cMap.h"
#include "cEnemyPersecutor.h"

//Resolution
#define SCREEN_RES_X	800
#define SCREEN_RES_Y	600

//Visible part
#define SCENE_WIDTH		20
#define SCENE_HEIGHT	17

//Dimension = Area^2
#define SCENE_AREA		32

//Map coordinate beginning
#define SCENE_Xo		0
#define SCENE_Yo		56
#define SCENE_Xf		( SCENE_Xo + (SCENE_WIDTH<<5) )
#define SCENE_Yf		( SCENE_Yo + (SCENE_HEIGHT<<5) )

//Radar position (left,top)
#define RADAR_Xo		672
#define RADAR_Yo		60
#define RADAR_Xf		800
#define RADAR_Yf		188

class cScene
{

public:
	
	cScene();
	virtual ~cScene();

	void Render(); //<- Pintara l'escena!!!
	void Update();

	void LoadMap(char *file);
	void Move(int pointer);
	void MoveByRadar(int x,int y);
	bool Visible(int cellx,int celly);

	cMap m_map;
	cPlayer m_player;
	cEnemyPersecutor m_enemy; // just to test: we will have more than one enemy

	int cx,cy;
};


#endif
