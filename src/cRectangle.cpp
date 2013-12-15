#include "cRectangle.h"
#include "Utils.h"

cRectangle::cRectangle()
{
	x = y = w = h = 0;
}
cRectangle::cRectangle(const cRectangle &aRect)
{
	SetRect(aRect.x, aRect.y, aRect.w, aRect.h);
}


cRectangle::cRectangle(int _x, int _y, int _w, int _h)
{
	SetRect(_x, _y, _w, _h);
}

void	cRectangle::SetRect(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

void	cRectangle::SetRect(int _x)
{
	x = _x;
	y = _x;
	w = _x;
	h = _x;
}

cRectangle::~cRectangle()
{
}

bool cRectangle::IsEmpty() const
{
	return ((w <= 0) || (h <= 0)) ? true : false;
}

bool cRectangle::Intersects(const cRectangle &_rect_check) const
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

std::string cRectangle::toString() const
{
	return std::string("x: " + util::toString(x) + " y: " + util::toString(y) + " w: " + util::toString(w) + " h: " + util::toString(h));
}

void cRectangle::reset()
{
	x = y = w = h = 0;
}

bool cRectangle::isEmpty() const
{
	return x == y == w == h == 0;
}

bool cRectangle::isInside(int a_x, int a_y) const
{
	return  a_x >= x && a_x <= x + w && a_y >= y && a_y <= y + h;
}
