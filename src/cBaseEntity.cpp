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

	DisableAnimation();
	StopAnimation();
	SetAnimationFramesPerStep(1);
}

void cBaseEntity::Update()
{
	UpdateAnimation();
}

void cBaseEntity::Render()
{
	if (!m_text_id.empty())
	{
		if (IsAnimationEnabled())
		{
			cRectangle buff = GetAnimationCurrentStepRectangle();
			cGame::Instance()->Graphics.DrawSprite(m_text_id, m_posx, m_posy, m_posz, &buff);
		}
		else
			cGame::Instance()->Graphics.DrawSprite(m_text_id, m_posx, m_posy, m_posz, &m_rect_texture);
	}
}

void cBaseEntity::RenderCollisionRect()
{
	if (IsCollidable())
	{
		
		//Renderitzo el rectangle a Z-1 perque surti per sobre la textura sempre
		cGame::Instance()->Graphics.DrawRect(GetCollisionRectAbsolute(), 0x00FF00FF, m_posz - 1);
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

void cBaseEntity::SetTextureID(const std::string &_str)
{
	m_text_id = _str;
	SetTextureSizesToTextureRect();
	SetTextureSizeToTextureRectRelative();
}

std::string& cBaseEntity::GetTextureID()
{
	return m_text_id;
}
void cBaseEntity::SetTextureRect(const cRectangle &_rect)
{
	m_rect_texture = _rect;
}

void cBaseEntity::SetCollisionRectRelative(const cRectangle &_rec)
{
	m_rect_colision_rel = _rec;
}

const cRectangle&  cBaseEntity::GetCollisionRectRelative() const
{
	return m_rect_colision_rel;
}

const cRectangle&  cBaseEntity::GetCollisionRectAbsolute() const
{
	cRectangle rect_absolute;
	rect_absolute.SetRect(m_posx + m_rect_colision_rel.x,
		m_posy + m_rect_colision_rel.y,
		m_rect_colision_rel.w,
		m_rect_colision_rel.h
		);
	return rect_absolute;
}

bool cBaseEntity::IsCollidable() const
{
	return m_collidable;
}

bool cBaseEntity::HasCollision(const cBaseEntity &_baseentity)
{
	if (IsCollidable() && _baseentity.IsCollidable())
		return GetCollisionRectAbsolute().Intersects(_baseentity.GetCollisionRectAbsolute());
	
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
		m_anim_curr_time_frame = 0;
		
	}
	else
	{
		cLog *Log = cLog::Instance();
		Log->Msg(std::string("SetAnimationCurrentStep out of range"));
		return;
	}

}

void cBaseEntity::PlayAnimation()
{
	SetAnimationCurrentStep(m_curr_anim_step);
	m_anim_run = true;
}

void cBaseEntity::StopAnimation()
{
	m_anim_run = false;
}

bool cBaseEntity::IsAnimationEnabled() const
{
	return m_animation_enabled;
}

bool cBaseEntity::IsPlayingAnimation() const
{
	return m_anim_run;
}

void cBaseEntity::EnableAnimation()
{
	m_animation_enabled = true;
}

void cBaseEntity::DisableAnimation()
{
	m_animation_enabled = false;
}

void cBaseEntity::ResetAnimation()
{
	SetAnimationCurrentStep(0);
}

const cRectangle & cBaseEntity::GetAnimationCurrentStepRectangle() const
{
	return m_anim_rect_bystep[m_curr_anim_step];
}

void cBaseEntity::UpdateAnimation()
{
	if (IsAnimationEnabled() && IsPlayingAnimation())
	{
		if (m_anim_curr_time_frame <= m_anim_time_frame)
		{
			m_anim_curr_time_frame++;
		}
		else
		{
			m_curr_anim_step = (m_curr_anim_step+1) % m_anim_rect_bystep.size();
			m_anim_curr_time_frame=0;
		}
	}
	
}


void cBaseEntity::SetAnimationFramesPerStep(const std::size_t _timeperstep)
{
	m_anim_time_frame = _timeperstep;
}

std::size_t cBaseEntity::GetAnimationFramesPerStep() const
{
	return m_anim_time_frame;
}

