#pragma once
#include <string>

#include "cRectangle.h"
#include <vector>

class cBaseEntity
{
public:
	cBaseEntity();
	
	virtual void Update();
	virtual void Render();

	//SPATIAL POSITION
	void SetPosition(int _x, int _y);
	void GetPosition(int &_x, int &_y);
	void SetZIndex(int _z);
	void GetZIndex(int &_z);
	
	//TEXTURE
	void SetTextureID(const std::string &_str);
	std::string& GetTextureID();
	void SetTextureRect(const cRectangle &_rect);
	void SetTextureSizesToTextureRect();

	//COLLISION
	void SetCollisionRectRelative(const cRectangle &_rec);
	const cRectangle& GetCollisionRectRelative() const;
	const cRectangle& GetCollisionRectAbsolute() const;
	void SetTextureSizeToTextureRectRelative();

	bool IsCollidable() const;
	void EnableCollision(){	m_collidable = true;};
	void DisableCollision(){ m_collidable = false; };
	bool HasCollision(const cBaseEntity &_baseentity);

	//ANIMATION
	void SetAnimationSteps(const std::vector<cRectangle> &_rect_steps);
	void GetAnimationSteps(std::vector<cRectangle> &_rect_steps);
	std::size_t GetAnimationCurrentStep();
	void SetAnimationCurrentStep(const std::size_t &_anim_step);

	//HELPERS
	void RenderCollisionRect();
	

	~cBaseEntity();

private:
	
	//ABSOLUTE POSITION UPPER LEFT
	int m_posx, m_posy;
	int m_posz;

	// texture id
	std::string m_text_id;
	cRectangle m_rect_texture; // Rect de seleccio de sprite dins de textura

	//Colision Rectangle
	bool m_collidable;
	cRectangle m_rect_colision_rel; //Actuara com a offset desde m_posx/y
	cRectangle m_rect_colision_abs; //Posicio absoluta real de la caixa de colisio
	void UpdateColisionRectAbsolute(); //Actualitza el rect absolut

	//Animation
	std::vector<cRectangle>	m_anim_rect_bystep;
	std::size_t m_curr_anim_step;
	
	
	


};

