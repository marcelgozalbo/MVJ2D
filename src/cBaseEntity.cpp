#include "cBaseEntity.h"


cBaseEntity::cBaseEntity()
{
	SetPosition(0,0);
	SetZIndex(0);
	SetCollisionRect(cRectangle());

}


cBaseEntity::~cBaseEntity()
{
}

void cBaseEntity::SetPosition(float _x, float _y)
{
	m_posx = _x;
	m_posy = _y;
}

void cBaseEntity::GetPosition(float &_x, float &_y)
{
	_x = m_posx;
	_y = m_posy;
}

void cBaseEntity::SetZIndex(int _z)
{
	m_posz = _z;

}
void cBaseEntity::GetZIndex(int &_z)
{
	_z = m_posz;
}

void cBaseEntity::SetCollisionRect(cRectangle &_rec)
{
	if (_rec.IsEmpty())
		m_collidable = false;
	else
		m_collidable = true;

	m_rect_colision = _rec;
}

cRectangle&  cBaseEntity::GetCollisionRect()
{
	return m_rect_colision;
}

bool cBaseEntity::IsCollidable()
{
	return m_collidable;
}

bool cBaseEntity::HasCollision(cBaseEntity &_baseentity)
{
	if (IsCollidable() && _baseentity.IsCollidable())
		return m_rect_colision.Intersects(_baseentity.GetCollisionRect());
	
	return false;
}