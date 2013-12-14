#include "cEnemyPersecutor.h"

cEnemyPersecutor::cEnemyPersecutor() :
	cCharacter("player", cRectangle(0, 0, 16, 24), 0, 0, 10, 3, 2, 3.0f)
{

}

cEnemyPersecutor::~cEnemyPersecutor()
{

}

void cEnemyPersecutor::Update()
{
	// think if we have to Move()

	cBaseEntity::Update();
}

void cEnemyPersecutor::Render()
{
	cBaseEntity::Render();
}
