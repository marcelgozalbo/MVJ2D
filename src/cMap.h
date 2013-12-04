#ifndef MPV2D_C_MAP_H_
#define MPV2D_C_MAP_H_

#include <fstream>
#include <array>
#include "cCell.h"

class cMap
{
public:
	cMap();
	~cMap();

	void load(const std::string& _filePath);
	void render();
	void update();

private:
	static const int tileCount = 2;

	typedef std::vector<cCell*> tRow;
	typedef std::vector<tRow> tGrid;
	typedef std::array<bool, tileCount> tWalkability;

	static tWalkability walkability;

	void clear();

	tGrid m_grid;
};

#endif
