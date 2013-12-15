#pragma once

#include "cCharacter.h"

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

private:
	void UpdateIdle();
	void UpdateAttack();
	void UpdateMovement();
	void MovePlayer(s32 xAmount, s32 yAmount);

	std::vector<cRectangle> m_DownSword, m_Down, m_DownShield, m_Up, m_UpShield, m_Right, m_RightShield, m_Left, m_LeftShield;
	std::vector<u32> m_StepsOrder;
	std::vector<u32> m_IdleStep;
	std::vector<u32> m_SwordSteps;
	E_PLAYER_STATE m_state;

};
