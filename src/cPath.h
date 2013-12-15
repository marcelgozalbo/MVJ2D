
#ifndef __PATH_H__
#define __PATH_H__

#include "cAStar.h"

//Direction
#define D_N		1
#define D_S		2
#define D_E		3
#define D_O		4
#define D_NE	5
#define D_NO	6
#define D_SE	7
#define D_SO	8

//Going
#define STOP		0
#define CONTINUE	1
#define ARRIVE		2

//Step length
#define STEP_LENGTH	2	//Posible values = {1,2,4,8,16,32}


class cPath
{
public:
	cPath();
	virtual ~cPath();

	int x,y;	//actual cell
	int xf,yf;	//objective cell
	int nxf,nyf;//new objective cell (superposed case)
	int dir;	//direction
	cAStar *AStar;
	int *world;

	void Make(int *map,int cx,int cy,int cxdest,int cydest);	//Make new path
	void ReMake(int *map,int cxdest,int cydest);				//Make new path overlapping previous
	int  NextStep(int *px,int *py,int *cx,int *cy);				//Calculate next step position

	int  Faced();
	bool IsDone();
	void Done();

private:
	int  NextCell();											//Calculate next cell
	void CalcDir(int x1,int y1,int x2,int y2);
};

#endif
