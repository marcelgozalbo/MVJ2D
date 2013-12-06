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
		unsigned int frameId;
		double duration;

		sFrameInfo() : frameId(0), duration(0) { }
		sFrameInfo(unsigned int fId, double d = 0) : frameId(fId), duration(d) { }
	};

	struct sCellInfo
	{
		tFrameVec frameVec;
		bool walkable;

		sCellInfo() : frameVec(), walkable(false) { }
		sCellInfo(const tFrameVec& frames, bool w = true) : frameVec(frames), walkable(w) { }
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
