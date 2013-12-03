#pragma once
#include <string>

#include "cRectangle.h"


class cBaseEntity
{
public:
	cBaseEntity();
	
	virtual void Update();
	virtual void Render();
	void RenderCollisionRect();

	//SPATIAL POSITION
	void SetPosition(float _x, float _y);
	void GetPosition(float &_x, float &_y);
	void SetZIndex(int _z);
	void GetZIndex(int &_z);
	
	//TEXTURE
	void SetTextureID(std::string &_str);
	std::string& GetTextureID();
	void SetTextureRect(cRectangle &_rect);
	void SetTextureSizesToTextureRect();

	//COLLISION
	void SetCollisionRectRelative(cRectangle &_rec);
	cRectangle& GetCollisionRectRelative();
	cRectangle& GetCollisionRectAbsolute();
	void SetTextureSizeToTextureRectRelative();

	bool IsCollidable();
	void EnableCollision(){	m_collidable = true;};
	void DisableCollision(){ m_collidable = false; };
	bool HasCollision(cBaseEntity &_baseentity);


	//HELPERS
	

	~cBaseEntity();

private:
	
	//ABSOLUTE POSITION UPPER LEFT
	float m_posx, m_posy;
	int m_posz;

	// texture id
	std::string m_text_id;
	cRectangle m_rect_texture;

	//Colision Rectangle
	bool m_collidable;
	cRectangle m_rect_colision_rel; //Actuara com a offset desde m_posx/y
	cRectangle m_rect_colision_abs; //Posicio absoluta real de la caixa de colisio
	void UpdateColisionRectAbsolute(); //Actualitza el rect absolut



};

