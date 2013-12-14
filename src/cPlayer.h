#pragma once

#include "cCharacter.h"

class cPlayer: public cCharacter
{
public:
	cPlayer();
	~cPlayer();

	void Update() override;
	void Render() override;

private:

	std::vector<cRectangle> m_Down,m_DownShield, m_Up, m_UpShield, m_Right, m_RightShield, m_Left, m_LeftShield;
	std::vector<u32> m_StepsOrder;
	std::vector<u32> m_IdleStep;
	
	
};
