#pragma once

#include "cCharacter.h"

class cPlayer: public cCharacter
{
public:

	enum E_PLAYER_STATE
	{
		E_IDLE = 0,
		E_MOVE,
		E_ATTACKING,
		E_HITANIM,
		E_DIEANIM,
		E_PLAYERDIED
	};
	cPlayer();
	~cPlayer();

	void Update() override;
	void Render() override;
	bool IsAlive();
	void respawn();
	void decrementLife();
private:
	void SetTextureFromOrientation();
	void LoadSteps(std::vector<cRectangle> &outvec, int startx, int starty, int numsteps, int ampladaframe, int alturaframe);
	void ChangeToIdle();
	void ChangeToAttack();
	void ChangeToMove();
	void ChangeToHitAnim();
	void ChangeToDieAnim();

	void UpdateIdle();
	void UpdateAttack();
	void UpdateMovement();
	void UpdateHitAnim();
	void UpdateDieAnim();
	void MovePlayer(s32 xAmount, s32 yAmount);

	std::vector<cRectangle> m_DownShield, m_UpShield, m_RightShield, m_LeftShield;
	std::vector<u32> m_StepsOrder;
	std::vector<u32> m_IdleStep;

	std::vector<cRectangle> m_DownSword, m_UpSword, m_LeftSword, m_RightSword;
	std::vector<u32> m_SwordSteps;
	E_PLAYER_STATE m_state;
	
	//Attacking
	cRectangle m_attack_col_rect;
	time_t lifeTime;

	// VIDA
	int m_life_count;
	void DrawLife();
	std::vector<cRectangle> m_HitSteps;
	std::vector<u32> m_hituporder, m_hitdownorder, m_hitrightorder, m_hitleftorder;
	time_t hitanimtime;

	//DIE ANIM
	time_t dieanimtime;
	std::vector<cRectangle> m_DieRects;
	
};
