
#ifndef __CRITTER_H__
#define __CRITTER_H__

#include <windows.h>
#include "cTrajectory.h"

class cScene;

typedef enum
{
	ORIENTATION_N = 0,
	ORIENTATION_NE,
	ORIENTATION_NO,
	ORIENTATION_S,
	ORIENTATION_SE,
	ORIENTATION_SO,
	ORIENTATION_E,
	ORIENTATION_O,
	
}CritterOrientation;

class cCritter
{
public:
	cCritter(void);
	virtual ~cCritter(void);
	void Update(void);
	void SetPosition(int posx,int posy);
	void GetPosition(int *posx,int *posy);


	//USELESS
	void GoToCell(int destcx,int destcy);
	void GoToEnemy(int destcx,int destcy);
	void Move();
	void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetRectRadar(RECT *rc,int *posx,int *posy);

	void SetCell(int cellx,int celly);
	void GetCell(int *cellx,int *celly);
	void SetSelected(bool sel);
	bool GetSelected();
	bool GetShooting();
	bool IsFiring();

private:
	int x,y;		//Position in total map
	CritterOrientation m_orientation;



	// USELESS
	int cx,cy;		//Cell position in total map
	bool selected;	//Selected for move or attack

	cTrajectory Trajectory;

	int seq;		//Sequence animation control
	int delay;		//Animation delay

	bool attack;	//Order to attack established (moving for attack)
	bool shoot;		//Begin attack (to shoot)
	int shoot_seq;	//Shooter sequence animation control
	int shoot_delay;//Shooter animation delay
};

#endif