
#include "cScene.h"
#include "cMouse.h"
#include <stdio.h>
#include <iostream>
#include "cGame.h"

cScene::cScene() :
	m_debugFont("arial", "", 100, cRectangle(0, 0, 300, 100), 0xFFFFFFFF, cFont::ALIGN_LEFT)
{
	cx=0;
	cy=0;

	m_enemy.SetPosition(50, 50);
}

cScene::~cScene()
{

}

void cScene::Update()
{
	m_map.update();
	m_player.Update();
	m_enemy.Update();
	m_debugFont.setText("playerRect -> " + m_player.GetCollisionRectAbsolute().toString());
}

void cScene::Render()
{
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	// TESTING SHIT
	m_map.render();
	m_player.Render();
	m_enemy.Render();
	m_debugFont.render();
	
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

