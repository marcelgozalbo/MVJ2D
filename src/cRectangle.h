#pragma once

#include <string>

class cRectangle
{
public:
	cRectangle();
	cRectangle(const cRectangle &);
	cRectangle(int _x, int _y, int _w, int _h);


	void		SetRect(int _x, int _y, int _w, int _h);
	void		SetRect(int _x);
	bool		Intersects(const cRectangle &_rect_check) const;
	bool		IsEmpty() const;
	std::string toString() const;

	~cRectangle();

	int x;
	int y;
	int w;
	int h;
};

