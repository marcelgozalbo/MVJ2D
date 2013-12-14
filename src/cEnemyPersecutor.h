#ifndef MPV2D_CENEMY_PERSECUTOR_H_
#define MPV2D_CENEMY_PERSECUTOR_H_

#include "cCharacter.h"

class cEnemyPersecutor : public cCharacter
{
public:
	cEnemyPersecutor();
	~cEnemyPersecutor();

	void Update() override;
	void Render() override;

private:
};

#endif
