#pragma once

#include "cCharacter.h"
#include "cSound.h"

class cPlayer: public cCharacter
{
public:

	enum E_PLAYER_STATE
	{
		E_IDLE = 0,
		E_MOVE,
		E_ATTACKING

	};
	cPlayer();
	~cPlayer();

	void Update() override;
	void Render() override;
	bool IsAlive() { if (m_life_count) return true; else return false; };
	void respawn();
	void decrementLife();
private:
	void SetTextureFromOrientation();
	void LoadSteps(std::vector<cRectangle> &outvec, int startx, int starty, int numsteps, int ampladaframe, int alturaframe);
	void ChangeToIdle();
	void ChangeToAttack();
	void ChangeToMove();

	void UpdateIdle();
	void UpdateAttack();
	void UpdateMovement();
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

	cSound::tSoundId _sound_attack;
	cSound::tSoundId _sound_hit;
};
