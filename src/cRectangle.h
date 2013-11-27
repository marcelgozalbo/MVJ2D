#pragma once

class cRectangle
{
public:
	cRectangle();
	cRectangle(int _x, int _y, int _w, int _h);

	bool	Intersects(const cRectangle &_rect_check);
	bool	IsEmpty() const;

	~cRectangle();
private:

	int x;
	int y;
	int w;
	int h;
};

