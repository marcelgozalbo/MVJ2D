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
		unsigned int duration;

		sFrameInfo() : framePosX(0), framePosY(0), duration(0) { }
		sFrameInfo(unsigned int posx, unsigned int posy, unsigned int d = 0) : framePosX(posx), framePosY(posy), duration(d) { }
	};

	struct sCellInfo
	{
		std::string tileSet;
		tFrameVec frameVec;
		bool walkable;

		sCellInfo() : tileSet(""), frameVec(), walkable(false) {}
		sCellInfo(const std::string& tileSet, const tFrameVec& frames, bool w = true) : tileSet(tileSet), frameVec(frames), walkable(w) { }
	};

	static const unsigned int tileWidth = 32;
	static const unsigned int tileHeight = 32;

	cCell(unsigned int _row, unsigned int _col, const sCellInfo& _cellInfo);
	~cCell();

	bool isWalkable() const;

	void render();
	void update();

private:
	bool m_walkable;
};

#endif
