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
	
};
