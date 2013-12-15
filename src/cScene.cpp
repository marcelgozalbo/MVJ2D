#include "cScene.h"
#include "cMouse.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "cGame.h"
#include "Utils.h"

#define ENEMY_COUNT 5

cScene::cScene() :
	m_debugFont("arial", "", 100, cRectangle(0, 0, 300, 100), 0xFFFFFFFF, cFont::ALIGN_LEFT),
	m_debugCellFont("arial", "", 100, cRectangle(0, 30, 300, 100), 0xFFFFFFFF, cFont::ALIGN_LEFT)
{
	cx=0;
	cy=0;
}

cScene::~cScene()
{

}

void cScene::LoadEnemies()
{
	s32 limitX, limitY;
	m_map.getLimits(&limitX, &limitY);

	for (u32 idx = 0; idx < ENEMY_COUNT; idx++)
	{
		cRectangle rect;
		rect.w = 300;
		rect.h = 300;
		do
		{
			rect.x = rand() % limitX;
			rect.y = rand() % limitY;
		} while (!m_map.isWalkable(rect));

		m_enemies.push_back(cEnemyPersecutor());
		m_enemies.back().SetPosition(rect.x, rect.y);
		m_enemies.back().SetPatrol(150, 150);
	}
}

//Chequejo i mato si dono a un enemic
void cScene::UpdateEnemyHit(const cRectangle &hitrect)
{
	for (u32 idx = 0; idx < m_enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = m_enemies[idx];

		if (enemy.GetCollisionRectAbsolute().Intersects(hitrect))
			enemy.Die();
	}
}

bool cScene::IsPlayerWon()
{
	bool allDead = true;

	for (u32 idx = 0; allDead && idx < m_enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = m_enemies[idx];
		allDead = allDead && !enemy.IsAlive();
	}

	if (m_player.IsAlive() && allDead)
		return true;
	
	return false;
}

bool cScene::IsPlayerLost()
{
	bool allDead = true;

	for (u32 idx = 0; allDead && idx < m_enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = m_enemies[idx];
		allDead = allDead && !enemy.IsAlive();
	}

	if (!m_player.IsAlive() && !allDead)
		return true;

	return false;
}

void cScene::Update()
{
	m_player.Update();

	for (u32 idx = 0; idx < m_enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = m_enemies[idx];
		enemy.Update();
	}

	m_map.update();

	// update debug font
	cRectangle playerRect = m_player.GetCollisionRectAbsolute();
	cRectangle debugRect = playerRect;
	debugRect.w = playerRect.x + playerRect.w;
	debugRect.h = playerRect.y + playerRect.h;
	s32 row, col, lastRow, lastCol;
	m_map.toCellCoord(playerRect.x, playerRect.y, &row, &col);
	m_map.toCellCoord(debugRect.w, debugRect.h, &lastRow, &lastCol);

	m_debugFont.setText(debugRect.toString() + " r: " + util::toString(row) + " c:" + util::toString(col) + " lr:" + util::toString(lastRow) + " lc:" + util::toString(lastCol)
		+ " wk:" + util::toString(m_map.isWalkable(playerRect)));

	// update debug cell font
	m_debugCellFont.setText(m_map.getCellDebugString(0, 3));
}

void cScene::Render()
{
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	
	m_player.Render();

	for (u32 idx = 0; idx < m_enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = m_enemies[idx];
		enemy.Render();
	}

	m_map.render();

	//m_debugFont.render();
	//m_debugCellFont.render();
	
	/*
	cBaseEntity a;
	a.SetTextureID(std::string("characters"));
	a.EnableCollision();
	//a.SetCollisionRectRelative(cRectangle(10, 10, 100, 100));
	a.Render();
	a.RenderCollisionRect();
	*/
	/*
	cRectangle rectangle3(0, 0, 256, 256);
	cGame::Instance()->Graphics.DrawSprite(std::string("Mainmenu"), 0, 0,50, &rectangle3);
	cRectangle rectangle4(0, 0, 128, 128);
	cGame::Instance()->Graphics.DrawSprite(std::string("GUI"), 0, 0,30, &rectangle4);

	
	//cRectangle rectangle2(32, 32, 128, 128);
	cGame::Instance()->Graphics.DrawRect(rectangle4, D3DCOLOR(0x0000FF00),10);

	//cRectangle rectangle(0, 0, 256, 256);
	cGame::Instance()->Graphics.DrawRect(rectangle3, D3DCOLOR(0x00FF0000),20);
	*/
}

void cScene::LoadMap(char *file)
{
	m_map.load(file);
}

void cScene::Move(int pointer)
{
	//map=32x32, visible=20x17 => move=0..32-20,0..32-17=0..12,0..15

	//Up
	if((pointer==MN)||(pointer==MNO)||(pointer==MNE))
	{
		if(cy>0) cy--;
	}
	//South
	else if((pointer==MS)||(pointer==MSO)||(pointer==MSE))
	{
		if(cy<SCENE_AREA-SCENE_HEIGHT) cy++;
	}
	//West
	if((pointer==MO)||(pointer==MNO)||(pointer==MSO))
	{
		if(cx>0) cx--;
	}
	//East
	else if((pointer==ME)||(pointer==MNE)||(pointer==MSE))
	{
		if(cx<SCENE_AREA-SCENE_WIDTH) cx++;
	}
}

void cScene::MoveByRadar(int x,int y)
{
	//move=0..12,0..15
	//rect=(80x68)/4=20x17

	cx=(x-RADAR_Xo)>>2;
	cy=(y-RADAR_Yo)>>2;

	if(cx<=9)		cx=0;
	else if(cx>=21)	cx=12;
	else			cx-=9;
	
	if(cy<=8)		cy=0;
	else if(cy>=23)	cy=15;
	else			cy-=8;
}

bool cScene::Visible(int cellx,int celly)
{
	return ((cellx>=cx)&&(cellx<cx+SCENE_WIDTH)&&(celly>=cy)&&(celly<cy+SCENE_HEIGHT)) ? 1 : 0;
}

