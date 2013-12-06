#ifndef MPV2D_C_MAP_H_
#define MPV2D_C_MAP_H_

#include <fstream>
#include <array>
#include <unordered_map>
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
	struct sFrameInfo;
	struct sCellInfo;

	typedef std::vector<cCell*> tRow;
	typedef std::vector<tRow> tGrid;
	typedef std::vector<sFrameInfo> tFrameVec;
	typedef std::unordered_map<unsigned int, sCellInfo> tAnimations;

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

		sCellInfo() : frameVec(), walkable (false) { }
		sCellInfo(const tFrameVec& frames, bool w = true) : frameVec(frames), walkable(w) { }
	};

	void clear();
	void loadAnimations(std::ifstream& file);
	void loadMap(std::ifstream& file);

	tGrid m_grid;
	tAnimations m_animations;
};

#endif
