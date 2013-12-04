#include "cBaseEntity.h"
#include "cGame.h"
#include "cLog.h"

cBaseEntity::cBaseEntity()
{
	SetPosition(0,0);
	SetZIndex(0);
	SetTextureID(std::string(""));
	SetCollisionRectRelative(cRectangle());
	DisableCollision();

}

void cBaseEntity::Update()
{
	UpdateColisionRectAbsolute();
}

void cBaseEntity::Render()
{
	if (!m_text_id.empty())
		cGame::Instance()->Graphics.DrawSprite(m_text_id,m_posx,m_posy,m_posz,&m_rect_texture);
}

void cBaseEntity::RenderCollisionRect()
{
	if (IsCollidable())
	{
		//Renderitzo el rectangle a Z-1 perque surti per sobre la textura sempre
		cGame::Instance()->Graphics.DrawRect(m_rect_colision_abs, 0x00FF00FF, m_posz - 1);
	}
}


cBaseEntity::~cBaseEntity()
{
}

void cBaseEntity::SetPosition(int _x, int _y)
{
	m_posx = _x;
	m_posy = _y;
}

void cBaseEntity::GetPosition(int &_x, int &_y)
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

void cBaseEntity::SetTextureID(std::string &_str)
{
	m_text_id = _str;
	SetTextureSizesToTextureRect();
	SetTextureSizeToTextureRectRelative();
}

std::string& cBaseEntity::GetTextureID()
{
	return m_text_id;
}
void cBaseEntity::SetTextureRect(cRectangle &_rect)
{
	m_rect_texture = _rect;
}

void cBaseEntity::SetCollisionRectRelative(cRectangle &_rec)
{
	m_rect_colision_rel = _rec;
	UpdateColisionRectAbsolute();
}

void cBaseEntity::UpdateColisionRectAbsolute()
{
	m_rect_colision_abs.SetRect(m_posx + m_rect_colision_rel.x,
		m_posy + m_rect_colision_rel.y,
		m_rect_colision_rel.w,
		m_rect_colision_rel.h
		);
}

cRectangle&  cBaseEntity::GetCollisionRectRelative()
{
	return m_rect_colision_rel;
}

cRectangle&  cBaseEntity::GetCollisionRectAbsolute()
{
	return m_rect_colision_abs;
}

bool cBaseEntity::IsCollidable()
{
	return m_collidable;
}

bool cBaseEntity::HasCollision(cBaseEntity &_baseentity)
{
	if (IsCollidable() && _baseentity.IsCollidable())
		return m_rect_colision_abs.Intersects(_baseentity.GetCollisionRectAbsolute());
	
	return false;
}

void cBaseEntity::SetTextureSizesToTextureRect()
{
	m_rect_texture.SetRect(0);
	cGame::Instance()->Graphics.GetTextureSizes(m_text_id, m_rect_texture.h, m_rect_texture.w);
}


void cBaseEntity::SetTextureSizeToTextureRectRelative()
{
	cRectangle rec;
	cGame::Instance()->Graphics.GetTextureSizes(m_text_id, rec.h, rec.w);
	SetCollisionRectRelative(rec);
}

void cBaseEntity::SetAnimationSteps(const std::vector<cRectangle> &_rect_steps)
{
	if (!_rect_steps.empty())
	{
		m_anim_rect_bystep = _rect_steps;
		SetAnimationCurrentStep(0);
		
	}
}


void cBaseEntity::GetAnimationSteps(std::vector<cRectangle> &_rect_steps)
{
	_rect_steps = m_anim_rect_bystep;
}

std::size_t cBaseEntity::GetAnimationCurrentStep()
{
	return m_curr_anim_step;

}

void cBaseEntity::SetAnimationCurrentStep(const std::size_t &_anim_step)
{
	if (_anim_step < m_anim_rect_bystep.size() )
	{
		m_curr_anim_step = _anim_step;
		m_rect_texture = m_anim_rect_bystep[m_curr_anim_step];
	}
	else
	{
		cLog *Log = cLog::Instance();
		Log->Msg(std::string("SetAnimationCurrentStep out of range"));
		return;
	}

}