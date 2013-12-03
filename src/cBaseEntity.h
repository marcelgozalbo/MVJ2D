#pragma once
#include <string>

#include "cRectangle.h"


class cBaseEntity
{
public:
	cBaseEntity();
	
	void Update();
	void Render();

	void SetPosition(float _x, float _y);
	void GetPosition(float &_x, float &_y);

	void SetZIndex(int _z);
	void GetZIndex(int &_z);
	
	void SetCollisionRect(cRectangle &_rec);
	cRectangle& GetCollisionRect();

	bool IsCollidable();
	bool HasCollision(cBaseEntity &_baseentity);
	~cBaseEntity();

private:
	
	//position
	float m_posx, m_posy;
	int m_posz;

	// texture id
	std::string text_id;

	//Colision Rectangle
	bool m_collidable;
	cRectangle m_rect_colision;



};

