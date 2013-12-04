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

private:
	typedef std::vector<int> tRow;
	typedef std::vector<tRow> tGrid;

	tGrid m_grid;
};

#endif
