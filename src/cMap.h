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
	bool isWalkableFor(const cBaseEntity& entity) const;

private:
	typedef std::vector<cCell*> tRow;
	typedef std::vector<tRow> tGrid;
	typedef std::unordered_map<unsigned int, cCell::sCellInfo> tAnimations;

	void clear();
	void loadAnimations(std::ifstream& file);
	void loadMap(std::ifstream& file);
	void fatalError(const std::string& errorText);

	tGrid m_grid;
	tAnimations m_animations;
};

#endif
