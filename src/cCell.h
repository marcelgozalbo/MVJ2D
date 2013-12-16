#ifndef MPV2D_CELL_H_
#define MPV2D_CELL_H_

#include "cBaseEntity.h"

class cCell : public cBaseEntity
{
public:
	struct sFrameInfo;

	typedef std::vector<sFrameInfo> tFrameVec;

	struct sFrameInfo
	{
		unsigned int framePosX;
		unsigned int framePosY;

		sFrameInfo() : framePosX(0), framePosY(0) { }
		sFrameInfo(unsigned int posx, unsigned int posy) : framePosX(posx), framePosY(posy) { }
	};

	struct sCellInfo
	{
		std::string tileSet;
		tFrameVec frameVec;
		bool walkable;
		unsigned int duration;
		unsigned int z;

		sCellInfo() : tileSet(""), frameVec(), walkable(false), duration(0), z(1) {}
		sCellInfo(const std::string& tileSet, const tFrameVec& frames, bool w = true, unsigned int d = 0, unsigned int cz = 1) : tileSet(tileSet), frameVec(frames), walkable(w), duration(d), z(cz) { }
	};

	static const int tileWidth = 32;
	static const int tileHeight = 32;

	cCell(unsigned int _row, unsigned int _col, const sCellInfo& _cellInfo);
	~cCell();

	void render();
	void update();
	bool isWalkable() const;
	std::string toString() const;

private:
	bool m_walkable;
};

#endif
