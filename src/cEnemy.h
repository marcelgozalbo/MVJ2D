#ifndef MPV2D_CENEMY_H_
#define MPV2D_CENEMY_H_

#include "cCharacter.h"

enum eEnemyType
{
	ENEMY_TYPE_PERSECUTOR = 0,
};

class cEnemy : public cCharacter
{
public:
	cEnemy(eEnemyType type);
	~cEnemy();

	void Update() override;
	void Render() override;

private:
};

#endif
