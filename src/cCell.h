#ifndef MPV2D_CELL_H_
#define MPV2D_CELL_H_

#include "cBaseEntity.h"

class cCell : public cBaseEntity
{
public:
	cCell(int _row, int _col, int _cellId, bool _walkable);
	~cCell();

	bool isWalkable() const;

	void render();
	void update();

private:
	static const int tileWidth = 32;
	static const int tileHeight = 32;

	bool m_walkable;
};

#endif
