
#ifndef __SCENE_H__
#define __SCENE_H__

#include "cPlayer.h"
#include "cMap.h"
#include "cEnemyPersecutor.h"
#include "cFont.h"
#include "cHeart.h"

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
	void LoadEnemies();
	void LoadHearts();

	bool IsPlayerWon();
	bool IsPlayerLost();

	cMap m_map;
	cPlayer m_player;
	cFont m_debugFont;
	cFont m_debugCellFont;
	cFont m_enemiesAlive;

	std::vector<cEnemyPersecutor> m_enemies;
	std::list<cHeart> m_hearts;


	void UpdateEnemyHit(const cRectangle &hitrect);
	void UpdatePlayerHit(const cRectangle &hitrect);
	int cx,cy;

private:

};


#endif
