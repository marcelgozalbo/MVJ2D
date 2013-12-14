#ifndef MPV2D_C_MAP_H_
#define MPV2D_C_MAP_H_

#include <fstream>
#include <array>
#include <unordered_map>
#include "types.h"
#include "cCell.h"

class cMap
{
public:
	cMap();
	~cMap();

	void load(const std::string& _filePath);
	void render();
	void update();
	bool isWalkable(const cRectangle& position) const;

	//debug
	std::string getCellDebugString(u32 row, u32 col);
	void toCellCoord(s32 x, s32 y, s32* row, s32* col);

private:
	typedef std::vector<cCell*> tRow;
	typedef std::vector<tRow> tGrid;
	typedef std::unordered_map<u32, cCell::sCellInfo> tAnimations;

	static u32 divAddRemainder(u32 dividend, u32 divisor);

	void clear();
	void loadAnimations(std::ifstream& file);
	void loadMap(std::ifstream& file);
	void fatalError(const std::string& errorText);
	cCell* getCell(u32 row, u32 col) const;

	tGrid m_grid;
	tAnimations m_animations;
};

#endif
