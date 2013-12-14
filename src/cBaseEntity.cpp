#include "cBaseEntity.h"
#include "cGame.h"
#include "cLog.h"
#include "cFont.h"
#include "Utils.h"
bool cBaseEntity::m_debug_collision = false;
bool cBaseEntity::m_debug_anim  = false;
bool cBaseEntity::m_debug_pos = false;




cBaseEntity::cBaseEntity(int x, int y, int z):
cBaseEntity()
{
	SetPosition(x, y);
	SetZIndex(z);
}

cBaseEntity::cBaseEntity(const std::string &texid, int x, int y, int z):
cBaseEntity(x,y,z)
{
	SetTextureID(texid);
}

cBaseEntity::cBaseEntity()
{
	SetVisible(true);

	SetPosition(0,0);
	SetZIndex(0);

	SetTextureID("");
	SetTextureScale(1.0f);
	
	SetCollisionRectRelative(cRectangle());
	DisableCollision();

	DisableAnimation();
	StopAnimation();
	SetAnimationFramesPerStep(1);

	DisableDebugMode();
	
}

void cBaseEntity::Update()
{
	UpdateAnimation();


	cInputLayer  &input = cGame::Instance()->Input;
	if (input.KeyDown(DIK_F5))
		EnableColDebugMode();
	else
		DisableColDebugMode();

	if (input.KeyDown(DIK_F6))
		EnableDebugAnimMode();
	else
		DisableDebugAnimMode();

	if (input.KeyDown(DIK_F7))
	{
		EnableDebugPosMode();		
	}
	else
	{
		DisableDebugPosMode();
	}
	
	if (input.KeyDown(DIK_F8))
	{
		EnableDebugAnimMode();
		EnableColDebugMode();
		EnableDebugPosMode();
	}
	


}

void cBaseEntity::Render()
{
	if (m_Visible && !m_text_id.empty())
	{
		if (IsAnimationEnabled())
		{
			cGame::Instance()->Graphics->DrawSprite(m_text_id, m_posx, m_posy, m_posz, GetAnimationCurrentStepRectangle(),scalex, scaley, scalez);
		}
		else
			cGame::Instance()->Graphics->DrawSprite(m_text_id, m_posx, m_posy, m_posz, m_rect_texture,scalex,scaley,scalez);

	}

	if (m_debug_mode)
	{
		if (m_debug_collision)
			RenderCollisionRect();

		if (m_debug_anim)
			RenderAnimInfoDebug();

		if (m_debug_pos)
			RenderPosInfoDebug();
	}
}

bool cBaseEntity::IsVisible() const
{
	return m_Visible;
}

void cBaseEntity::SetVisible(bool aVisible)
{
	m_Visible = aVisible;
}

void cBaseEntity::RenderCollisionRect()
{
	if (IsCollidable())
	{
		
		//Renderitzo el rectangle a Z+1 perque surti per sobre la textura sempre
		cGame::Instance()->Graphics->DrawRect(GetCollisionRectAbsolute(), 0x00FF00FF, m_posz + 1);
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
	if (!_str.empty())
	{
		m_text_id = _str;
		SetTextureSizesToTextureRect();
		SetTextureSizeToCollisionRectRelative();
	}
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

cRectangle  cBaseEntity::GetCollisionRectAbsolute() const
{
	cRectangle rect_absolute;
	rect_absolute.SetRect(
		static_cast<s32>(m_posx + m_rect_colision_rel.x),
		static_cast<s32>(m_posy + m_rect_colision_rel.y),
		static_cast<s32>((m_rect_colision_rel.w) * scalex),
		static_cast<s32>((m_rect_colision_rel.h) * scaley)
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
	cGame::Instance()->Graphics->GetTextureSizes(m_text_id, m_rect_texture.h, m_rect_texture.w);
}

void cBaseEntity::SetTextureScale(float _scale)
{
	SetTextureScale(_scale, _scale, _scale);
}

void cBaseEntity::SetTextureScale(float _scalex, float _scaley, float _scalez)
{
	scalex = _scalex; scaley = _scaley; scalez = _scalez;
}

void cBaseEntity::SetTextureSizeToCollisionRectRelative()
{
	cRectangle rec;
	cGame::Instance()->Graphics->GetTextureSizes(m_text_id, rec.h, rec.w);
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

void cBaseEntity::RenderAnimInfoDebug()
{
	std::string text("AnimInfo[" + util::toString(m_curr_anim_step) +"]\n"+ m_anim_rect_bystep[m_curr_anim_step].toString());
	auto rec = GetCollisionRectAbsolute();
	rec.x += rec.w + 2;
	rec.w = 0;
	rec.h = 0;
	cGame::Instance()->Graphics->DrawFont("arial", text, m_posz + 1, rec);

}

void cBaseEntity::RenderPosInfoDebug()
{
	
	std::string text("Pos: x: " + util::toString(m_posx) + " y: " + util::toString(m_posy) +	" z: " 	+ util::toString(m_posz)+"\n"
		+"ColAbs: " +GetCollisionRectAbsolute().toString()
		+"\nColRel"+GetCollisionRectRelative().toString());
	
	cRectangle postext(m_posx, m_posy - 50, 0, 0);
	cGame::Instance()->Graphics->DrawFont("arial", text, m_posz + 1, postext);

}