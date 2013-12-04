#ifndef MPV2D_C_MAP_H_
#define MPV2D_C_MAP_H_

#include "cBaseEntity.h"
#include <fstream>

class ifstream;

class cMap
{
public:
	cMap();
	~cMap();

	void load(const std::string& _filePath);
	void render();
	void update();

private:
	typedef std::vector<int> tRow;
	typedef std::vector<tRow> tGrid;

	static const int tileWidth = 32;
	static const int tileHeight = 32;

	tGrid m_grid;
};

#endif
