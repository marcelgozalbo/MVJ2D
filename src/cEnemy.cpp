#include "cEnemy.h"

cEnemy::cEnemy(eEnemyType type) :
	cCharacter()
{
	switch (type)
	{
	case ENEMY_TYPE_PERSECUTOR:
		//#todo: initialize character
		//Init(textureId, textureRect, x, y, z, vStraight, vDiagonal, textureScale)
		break;
	}
}

cEnemy::~cEnemy()
{

}

void cEnemy::Update()
{
	// think if we have to Move()

	cBaseEntity::Update();
}

void cEnemy::Render()
{
	cBaseEntity::Render();
}
