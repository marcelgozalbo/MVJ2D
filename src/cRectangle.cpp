#include "cRectangle.h"


cRectangle::cRectangle()
{
	x = y = w = h = 0;
}

cRectangle::cRectangle(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

cRectangle::~cRectangle()
{
}

bool cRectangle::IsEmpty() const
{
	return ((w <= 0) || (h <= 0)) ? true : false;
}

bool cRectangle::Intersects(const cRectangle &_rect_check)
{
	

	if (this->IsEmpty() || _rect_check.IsEmpty())
		return false;
	

	int Amin, Amax, Bmin, Bmax;
	
	//Interseccio horitzonal
	Amin = x;
	Amax = Amin + w;
	Bmin = _rect_check.x;
	Bmax = Bmin + _rect_check.w;
	if (Bmin > Amin)
		Amin = Bmin;
	if (Bmax < Amax)
		Amax = Bmax;
	if (Amax <= Amin)
		return false;

	//Interseccio vertical
	Amin = y;
	Amax = Amin + h;
	Bmin = _rect_check.y;
	Bmax = Bmin + _rect_check.h;
	if (Bmin > Amin)
		Amin = Bmin;
	if (Bmax < Amax)
		Amax = Bmax;
	if (Amax <= Amin)
		return false;

	return true;
}
