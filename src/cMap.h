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
	void update();
	void render();
	bool isWalkable(const cRectangle& position) const;
	bool movePlayer(const cRectangle& position);
	bool moveEnemy(const cRectangle& position);
	bool insideLimits(const cRectangle& position);
	bool insideScreen(const cRectangle& position);
	int* getVisibleCells();
	void getLimits(s32* limitX, s32* limitY);
	void reset();

	//debug
	std::string getCellDebugString(u32 row, u32 col);
	void toCellCoord(s32 x, s32 y, s32* row, s32* col) const;

private:
	enum eMovementDirection
	{
		DIRECTION_NONE,
		DIRECTION_EAST,
		DIRECTION_WEST,
		DIRECTION_SOUTH,
		DIRECTION_NORTH
	};

	typedef std::vector<cCell*> tRow;
	typedef std::vector<tRow> tGrid;
	typedef std::unordered_map<u32, cCell::sCellInfo> tAnimations;

	static u32 divAddRemainder(u32 dividend, u32 divisor);

	void clear();
	void loadAnimations(std::ifstream& file);
	void loadMap(std::ifstream& file);
	void fatalError(const std::string& errorText);
	cCell* getCell(u32 row, u32 col) const;
	bool isWalkableFor(const cRectangle& position, s32 originRow, s32 originCol) const;
	void repositionEnemies(eMovementDirection direction);

	tGrid m_grid;
	tAnimations m_animations;

	s32 m_originRow;
	s32 m_originCol;
	s32 m_visibleRows;
	s32 m_visibleCols;
	s32 m_totalRows;
	s32 m_totalCols;
};

#endif
