#pragma once
#include <string>

#include "cRectangle.h"
#include <vector>

class cBaseEntity
{
public:
	cBaseEntity(int x, int y, int z);
	cBaseEntity(const std::string &texid, int x, int y, int z);
	cBaseEntity();
	
	virtual void Update();
	virtual void Render();

	//VISIBILITY
	bool IsVisible() const;
	void SetVisible(bool aVisible);

	//SPATIAL POSITION
	void SetPosition(int _x, int _y);
	void SetAbsolutePosition(int _x, int _y);
	void GetPosition(int &_x, int &_y);
	void GetAbsolutePosition(int& _x, int& _y) const;
	void SetZIndex(int _z);
	void GetZIndex(int &_z);
	
	//TEXTURE
	void SetTextureID(const std::string &_str);
	std::string& GetTextureID();
	void SetTextureRect(const cRectangle &_rect);
	void SetTextureSizesToTextureRect();
	void SetTextureScale(float _scale);
	void SetTextureScale(float _scalex, float _scaley, float _scalez);

	//COLLISION
	void SetCollisionRectRelative(const cRectangle &_rec);
	const cRectangle& GetCollisionRectRelative() const;
	cRectangle GetCollisionRectAbsolute() const;
	void SetTextureSizeToCollisionRectRelative();

	bool IsCollidable() const;
	void EnableCollision(){	m_collidable = true;};
	void DisableCollision(){ m_collidable = false; };
	bool HasCollision(const cBaseEntity &_baseentity);

	//ANIMATION
	void SetAnimationSteps(const std::vector<cRectangle> &_rect_steps);
	void GetAnimationSteps(std::vector<cRectangle> &_rect_steps);
	void SetAnimationFramesPerStep(const std::size_t _timeperstep);
	std::size_t GetAnimationFramesPerStep() const;
	const std::size_t GetAnimationFramesPerStep(const std::size_t _timeperstep);
	std::size_t GetAnimationCurrentStep();
	const cRectangle & GetAnimationCurrentStepRectangle() const;
	void SetAnimationCurrentStep(const std::size_t &_anim_step);
	void PlayAnimation();
	void StopAnimation();
	bool IsPlayingAnimation() const;
	void ResetAnimation();
	void UpdateAnimation();

	bool IsAnimationEnabled() const;
	void EnableAnimation();
	void DisableAnimation();

	//HELPERS
	void EnableDebugMode(){ m_debug_mode = true; };
	void DisableDebugMode(){ m_debug_mode = false; };
	bool IsDebugMode(){ return m_debug_mode; };


	void RenderCollisionRect();
	void EnableColDebugMode(){ m_debug_collision = true; };
	void DisableColDebugMode(){ m_debug_collision = false; };
	bool IsColDebugMode(){ return m_debug_collision; };

	void RenderAnimInfoDebug();
	void EnableDebugAnimMode(){ m_debug_anim = true; };
	void DisableDebugAnimMode(){ m_debug_anim = false; };
	bool IsDebugAnimMode(){ return m_debug_anim; };

	void RenderPosInfoDebug();
	void EnableDebugPosMode(){ m_debug_pos = true; };
	void DisableDebugPosMode(){ m_debug_pos = false; };
	bool IsDebugPosMode(){ return m_debug_pos; };

	virtual ~cBaseEntity();

private:
	
	//VISIBILITY
	bool m_Visible;

	//ABSOLUTE POSITION UPPER LEFT
	int m_posx, m_posy;
	int m_posz;

	// texture id
	std::string m_text_id;
	cRectangle m_rect_texture; // Rect de seleccio de sprite dins de textura
	float scalex, scaley, scalez;

	//Colision Rectangle
	bool m_collidable;
	cRectangle m_rect_colision_rel; //Actuara com a offset desde m_posx/y

	//Animation
	std::vector<cRectangle>	m_anim_rect_bystep;
	bool m_animation_enabled;
	bool m_anim_run;
	std::size_t m_curr_anim_step;
	std::size_t m_anim_time_frame; //quantitat de frames que han de passar per canviar d'step
	std::size_t m_anim_curr_time_frame; //quantitat de frames que han passat desde l'ultim canvi d'step
	
	static bool m_debug_collision;
	static bool m_debug_anim;
	bool m_debug_mode;
	static bool m_debug_pos;

};

